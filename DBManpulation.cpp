// DBManpulation.cpp: implementation of the CDBManpulation class.
// 
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ARSDocument.h"
#include "KeyWord.h"
#include "IndexTermsInDoc.h"
#include "ARS.h"
#include "DBManpulation.h"
#include "fstream.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////// ADO PREPARATION //////////
 struct InitOle {
InitOle()  { ::CoInitialize(NULL); }
~InitOle() { ::CoUninitialize();   }
} _init_InitOle_;

#define adEmpty 0

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CDBManpulation::CDBManpulation()
{
	hr				= S_OK;
	pConnection     = NULL;
	Rs				= NULL;
	MaxTerm			= 0;
	MaxDoc			= 0;
	MinDoc			= 0;
}
CDBManpulation::~CDBManpulation()
{
	CloseConnection();
}

BOOL CDBManpulation::MatchCommonWord(char* szWordValue)
{
	WordStruct* pWS;
	return ( CommonWordCollection.Lookup(szWordValue, ( CObject*& )pWS) );
//////////////////////// old thoughts of matching /////////////////////////////
/*	char szMatchQuery[80] = "SELECT * FROM TCommonWord WHERE CommonWordValue =\"";
	strcat(szMatchQuery, szWordValue);
	strcat(szMatchQuery, "\"");
	BOOL bState  = TRUE;

	hr = Rs->Open(szMatchQuery, _variant_t((IDispatch *) pConnection, TRUE),
				ADODB::adOpenStatic,
				ADODB::adLockReadOnly,
				-1 );
	if (!hr)
	{
		if(Rs->BOF)
		{
//			::MessageBox( NULL, "No records in the table", "", MB_OK );
			bState = FALSE;
		}
		else
		{
			bState = TRUE;
		}
	}
	else
	{
		AfxMessageBox("FAIL WITH DB IN PROCESSING QUERY");
		bState = TRUE;
	}
	hr = Rs->Close();
	return bState;
/////////////////////// end of bad thoughts ///////////////////////////
*/
}

BOOL CDBManpulation::OpenConnection()
{
	char* sConn = "ARSDB.accdb";
   //char *sConn = "C:\\My Documents\\projects\\db\\ARSDB.MDB";
/**/	//char *sConn = "C:\\My Documents\\test10\\ARSDB10.MDB";

   //////////// Open a connection using the OLE DB Provider for Microsoft Jet.
	hr = pConnection.CreateInstance(__uuidof(ADODB::Connection));
	pConnection->Provider = "Microsoft.Jet.OLEDB.4.0";
	hr = pConnection->Open(sConn,"","",NULL);
/*	///////////////////////////////////////////////////////
	hr = pConnection->Open(_bstr_t("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=C:\\My Documents\\projects\\db\\ARSDB.MDB;"),
      _bstr_t(L""),
      _bstr_t(L""),
      ADODB::adModeUnknown);
	///////////////////////////////////////////////////////
*/
	hr = Rs.CreateInstance( __uuidof( ADODB::Recordset ) );
	return hr;
}

void CDBManpulation::CloseConnection()
{
	Rs = NULL;
	pConnection->Close();
	pConnection     = NULL;
}

BOOL CDBManpulation::GetDocumentInfoByName(char* DocLocation, CARSDocument& DocInfo)
{
	char szQuery[200] = 
		"SELECT * FROM TDocumentInfo WHERE Location = \"";
	strcat(szQuery, DocLocation);
	strcat(szQuery, "\"");
	BOOL bState = TRUE;
	hr = Rs->Open(szQuery, _variant_t((IDispatch *) pConnection, TRUE),
				ADODB::adOpenStatic,
				ADODB::adLockReadOnly,
				-1 );
	if (!hr)
	{
		if(Rs->BOF)
		{
			::MessageBox( NULL, "No records,GetDocInfo, some thing wrong in the db", "", MB_OK );
			bState = FALSE;
		}
		else
		{ //////////// binding the values from the table to ARSDocument. class //////
		  _variant_t vDocID, vIgnored, vNumber;
          vDocID	= Rs->GetCollect("DocID");
          vIgnored  = Rs->GetCollect("Ignored");
		  vNumber	= Rs->GetCollect("DocNumber");
		  ///// here i will pass the pervious variants to Documents class ///
		  strcpy(DocInfo.m_DocID ,vDocID.operator _bstr_t());
		  DocInfo.m_Ignored = vIgnored.operator short();
		  DocInfo.m_DocNumber = vNumber.operator long();
		  //////////////////////////////////////////////////////////////////
          //Rs->MoveNext();
		  bState = TRUE;
		}
	}
	else
	{
		AfxMessageBox("FAIL WITH DB IN PROCESSING QUERY");
		bState = TRUE;
	}
	hr = Rs->Close();
	return bState;
}
BOOL CDBManpulation::GetDocumentInfoByNumber(int DocNum,CARSDocument& DocInfo)
{
	char szQuery[200] = 
		"SELECT * FROM TDocumentInfo WHERE DocNumber = ";
	char buffer[20];   
	_variant_t vData;
	strcat(szQuery, itoa(DocNum,buffer, 10));
	//strcat(szQuery, "\"");
	BOOL bState = TRUE;
	hr = Rs->Open(szQuery, _variant_t((IDispatch *) pConnection, TRUE),
				ADODB::adOpenStatic,
				ADODB::adLockReadOnly,
				-1 );
	if (!hr)
	{
		if(Rs->BOF)
		{
			::MessageBox( NULL, "No records,GetDocInfo, some thing wrong in the db", "", MB_OK );
			bState = FALSE;
		}
		else
		{ //////////// binding the values from the table to ARSDocument. class //////
		  vData = Rs->GetCollect("DocID");
		  strcpy(DocInfo.m_DocID, vData.operator _bstr_t());
          vData = Rs->GetCollect("Location");
		  strcpy(DocInfo.m_Location, vData.operator _bstr_t());
          vData  = Rs->GetCollect("Ignored");
		  ///// here i will pass the pervious variants to Documents class ///
		  DocInfo.m_Ignored   = vData.operator short();
		  //////////////////////////////////////////////////////////////////
          //Rs->MoveNext();
		  bState = TRUE;
		}
	}
	else
	{
		AfxMessageBox("FAIL WITH DB IN PROCESSING QUERY");
		bState = TRUE;
	}
	hr = Rs->Close();
	return bState;
}

BOOL CDBManpulation::AddNewDoc(CStringList *FilesPathList)
{ //// i will use SQL technique for adding the new documents ///

	char szQuery[200] = 
		"INSERT INTO TDocumentInfo ( DocID, Location, Type) VALUES ( \'";
	BOOL bState  = TRUE;	
	CString FilePath, FileName;
	int PathLength = 0, nCutPos = 0;
	for(POSITION pos = FilesPathList->GetHeadPosition();pos!= NULL;)
	{
		FilePath = FilesPathList->GetNext(pos);
		PathLength = FilePath.GetLength();
		FilePath.MakeReverse();
		nCutPos = FilePath.Find("\\");
		FilePath.MakeReverse();
		FileName = FilePath.Right(nCutPos);
		strcat(szQuery,FileName.GetBuffer(nCutPos));
		strcat(szQuery,"\',\'");
		strcat(szQuery, FilePath.GetBuffer(PathLength));
		strcat(szQuery,"\',\'txt\')");
		hr = Rs->Open(szQuery, _variant_t((IDispatch *) pConnection, TRUE),
		ADODB::adOpenDynamic, ADODB::adLockOptimistic, ADODB::adCmdText);
		strcpy(szQuery , "INSERT INTO TDocumentInfo ( DocID, Location, Type) VALUES ( \'");
	}

//	hr = Rs->Close();
	//if (!hr)
	return hr;
	
}

BOOL CDBManpulation::LoadCommonWords()
{
	char szMatchQuery[] = "SELECT * FROM TCommonWord";
	BOOL bState  = TRUE;

	hr = Rs->Open(szMatchQuery, _variant_t((IDispatch *) pConnection, TRUE),
				ADODB::adOpenStatic,
				ADODB::adLockReadOnly,
				-1 );
	if (!hr)
	{
		if(Rs->BOF)
		{
			::MessageBox( NULL, "No records in the table", "", MB_OK );
			bState = FALSE;
		}
		else
		{
		//////////// binding the values from the table to CommonWord collection //////
		  _bstr_t  vWordValue;
		  
		  while(!Rs->adoEOF)
		  {
			  vWordValue = Rs->GetCollect("CommonWordValue");
			  CommonWordCollection.SetAt(vWordValue.operator const char *(), new WordStruct(vWordValue.operator char *()));
			  Rs->MoveNext();
		  }
        //////////////////////////////////////////////////////////////////
		  bState = TRUE;
		}
	}
	else
	{
		AfxMessageBox("FAIL WITH DB IN PROCESSING QUERY");
		bState = FALSE;
	}
	hr = Rs->Close();
///////////////////////////////////////////////////////////////////////////
/*
	{ // block for testing the output data from every phase 
		WordStruct*	pWC1;
		CString				key;
		CStdioFile	constfile("_testload.txt", CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		char 		strLine[80];
		
		//int CollectionCount = WordCountCollection.GetCount();
		for(POSITION pos = CommonWordCollection.GetStartPosition();pos!=NULL;)
		{
			CommonWordCollection.GetNextAssoc( pos, key, (CObject*&)pWC1);
			wsprintf(strLine,"%s\n",pWC1->WordValue);
			constfile.WriteString (strLine);
		}
		constfile.Close();
	}
/*///////////////////////////////////////////////////////////////////////*/
	return bState;
}

BOOL CDBManpulation::CheckDocBase()
{
	char szQuery[200] = "SELECT * FROM TDocumentInfo";
	BOOL bState = TRUE;
	hr = Rs->Open(szQuery, _variant_t((IDispatch *) pConnection, TRUE),
				ADODB::adOpenStatic,
				ADODB::adLockReadOnly,
				-1 );
	if (!hr)
	{
		if(Rs->BOF)
		{
			::MessageBox( NULL, "No records,GetDocInfo, some thing wrong in the db", "", MB_OK );
			bState = FALSE;
		}
		else
		{ 
			bState = TRUE;
		}
	}
	else
	{
		AfxMessageBox("FAIL WITH DB IN PROCESSING QUERY");
		bState = TRUE;
	}
	hr = Rs->Close();
	return bState;
}

BOOL CDBManpulation::AddNewTerm(CKeyWord KeyWordInfo)
{ //// i will use SQL technique for adding the new terms ///

	char szQuery[200] = 
		"INSERT INTO TKeyWord ( TermValue, GWeight, TermGFI) VALUES ( \'";
	char Buffer[34];
	BOOL bState  = TRUE;	
	strcat(szQuery, KeyWordInfo.m_TermValue);
	strcat(szQuery,"\',");
	DtoString(KeyWordInfo.m_GlobalWeight, szQuery);
	strcat( szQuery, "," );
	_itoa(KeyWordInfo.m_Gfi,Buffer,10);
	strcat(szQuery,Buffer);
	strcat(szQuery,")");
	hr = Rs->Open(szQuery, _variant_t((IDispatch *) pConnection, TRUE),
		ADODB::adOpenDynamic, ADODB::adLockOptimistic, ADODB::adCmdText);
//	hr = Rs->Close();
	//if (!hr)
	return hr;
}

void CDBManpulation::DtoString(float dValue, char *sValue)
{
	int  decimal, sign;
	CString buffer;
	buffer = _fcvt( dValue, 8, &decimal, &sign );
	if(sign)
	{
		buffer.Insert(0,'-');
		decimal++;
	}
	buffer.Insert(decimal,'.');
	strcat( sValue, buffer.GetBuffer( buffer.GetLength() ) );
}

BOOL CDBManpulation::GetTermInfoByName(char* TermValue, LONG &TermNum)
{
	char szQuery[200] = 
		"SELECT * FROM TKeyWord WHERE TermValue = \"";
	strcat(szQuery, TermValue);
	strcat(szQuery, "\"");
	BOOL bState = TRUE;
	hr = Rs->Open(szQuery, _variant_t((IDispatch *) pConnection, TRUE),
				ADODB::adOpenStatic,
				ADODB::adLockReadOnly,
				-1 );
	if (!hr)
	{
		if(Rs->BOF)
		{
			bState = FALSE;
		}
		else
		{ /////// binding the values from the table to ARSDocument. class //////
		  _variant_t  vNumber;
		  vNumber = Rs->GetCollect("TermNumber");
		  ///// here i will pass the pervious variants to the caller///
		  TermNum = vNumber.operator long();
		  //////////////////////////////////////////////////////////////////////
		  bState = TRUE;
		}
	}
	else
	{
		AfxMessageBox("FAIL WITH DB IN PROCESSING QUERY- TermValue");
		bState = TRUE;
	}
	hr = Rs->Close();
	return bState;
}

BOOL CDBManpulation::GetTermInfoByNum(LONG TNum, char *TVal)
{
	char szQuery[200] = 
		"SELECT * FROM TKeyWord WHERE TermNumber = ";
	char buffer[20];
	strcat(szQuery,itoa(TNum,buffer, 10) );
	//strcat(szQuery, "\"");
	BOOL bState = TRUE;
	hr = Rs->Open(szQuery, _variant_t((IDispatch *) pConnection, TRUE),
				ADODB::adOpenStatic,
				ADODB::adLockReadOnly,
				-1 );
	if (!hr)
	{
		if(Rs->BOF)
		{
			::MessageBox( NULL, "No records,NO TermInfo, some thing wrong in the db", "", MB_OK );
			bState = FALSE;
		}
		else
		{ //////////// binding the values from the table to ARSDocument. class //////
		  _variant_t  vTval;
		  vTval	= Rs->GetCollect("TermValue");
		  ///// here i will pass the pervious variants to the caller///
		  strcpy(TVal ,vTval.operator _bstr_t());
		  //////////////////////////////////////////////////////////////////
		  bState = TRUE;
		}
	}
	else
	{
		AfxMessageBox("FAIL WITH DB IN PROCESSING QUERY- TermValue");
		bState = TRUE;
	}
	hr = Rs->Close();
	return bState;
}

BOOL CDBManpulation::AddIndexTerm(CIndexTermsInDoc TermDocInfo)
{
	char szQuery[200] = 
		"INSERT INTO TIndexTermsInDoc ( DocNum, TermNum, Weight, DFi) VALUES (";
	char Buffer[34];
	BOOL bState  = TRUE;	
	_itoa(TermDocInfo.GetDocNum(),Buffer,10);
	strcat(szQuery, Buffer);
	strcat(szQuery,",");
	_itoa(TermDocInfo.GetTermNum(),Buffer,10);
	strcat(szQuery, Buffer);
	strcat(szQuery,",");
	DtoString((float)TermDocInfo.GetWeight(), szQuery);
	strcat( szQuery, "," );
	_itoa(TermDocInfo.GetFrequency(),Buffer,10);
	strcat(szQuery, Buffer);
	strcat(szQuery,")");
	hr = Rs->Open(szQuery, _variant_t((IDispatch *) pConnection, TRUE),
		ADODB::adOpenDynamic, ADODB::adLockOptimistic, ADODB::adCmdText);
//	hr = Rs->Close();
	//if (!hr)
	return hr;
}

BOOL CDBManpulation::UpdateDoc(BOOL bIgnored, int DocNum)
{
	char szQuery[200] = 
		"UPDATE TDocumentInfo SET Ignored = ";
	char Buffer[34];
	CARSDocument DocInfo;
	GetDocumentInfoByNumber(DocNum, DocInfo);
	_itoa(bIgnored, Buffer, 10);
	strcat(szQuery, Buffer);
	strcat(szQuery, " WHERE ( DocNumber = ");
	_itoa(DocNum, Buffer, 10);
	strcat(szQuery, Buffer);
	strcat(szQuery, ") ");
	hr = Rs->Open(szQuery, _variant_t((IDispatch *) pConnection, TRUE),
		ADODB::adOpenDynamic, ADODB::adLockOptimistic, ADODB::adCmdText);
	return hr;
}

void CDBManpulation::FillArray(mwArray &TMmat)
{
	LONG	Index;
	double *DocVector = new double[MaxTerm+1];
	if(DocVector == NULL)
	{
		AfxMessageBox("FAIL WITH Allocating DocVector");
		exit(0);
	}
	char szQuery[200], buffer[20];
	BOOL bState = TRUE; 
	_variant_t  vTval;
	mwArray		tempmw;
	int			xx;
///////////////////////////////////////////////////////////////
	for(;MinDoc <= MaxDoc;MinDoc++)
	{
		memset( DocVector, 0, (MaxTerm+1)*8);
		strcpy(szQuery, "SELECT * FROM TIndexTermsInDoc WHERE DocNum = ");
		strcat(szQuery, itoa(MinDoc,buffer, 10));
		hr = Rs->Open(szQuery, _variant_t((IDispatch *) pConnection, TRUE),
					ADODB::adOpenStatic,
					ADODB::adLockReadOnly,
					-1 );
		if (!hr)
		{
			if(Rs->BOF)
			{
				//::MessageBox( NULL, "No records,NO TermInfo, some thing wrong in the db", "", MB_OK );
				xx = MinDoc;
			}
			else
			{ //////////// filling the values from the table to DocVector //////
				while(!Rs->adoEOF)
				{
					vTval	= Rs->GetCollect("TermNum");
					///// here i will pass the pervious variants to the caller///
					Index = vTval.operator long();
					vTval	= Rs->GetCollect("Weight");
					DocVector[Index-1] = vTval.operator double();
					Rs->MoveNext();
					//////////////////////////////////////////////////////////////////
				}
			}
		}
		else
		{
			AfxMessageBox("FAIL WITH DB IN PROCESSING QUERY- TermValue");
		}
		hr = Rs->Close();
		tempmw =  mwArray(MaxTerm,1,DocVector);
		TMmat = horzcat(TMmat, tempmw);
	}// end of for loop ...
///////////////////////////////////////////////////////////////
//	TMmat = sparse(TMmat);
	delete[] DocVector;
}

BOOL CDBManpulation::GetDocTermInfo()
{
	BOOL bState = TRUE;
	_variant_t  vNumber;
	char szQuery[200] = 
		"SELECT MAX(TermNumber) AS [TMaxNum] FROM TKeyWord";
	hr = Rs->Open(szQuery, _variant_t((IDispatch *) pConnection, TRUE),
				ADODB::adOpenStatic,
				ADODB::adLockReadOnly,
				-1 );
	if (!hr)
	{
		if(Rs->BOF)
		{
			::MessageBox( NULL, "No records,NO TermInfo, some thing wrong in the db", "", MB_OK );
			bState = FALSE;
		}
		else
		{ /////// binding the values from the table to ARSDocument. class //////
		  vNumber = Rs->GetCollect("TMaxNum");
		  ///// here i will pass the pervious variants to the caller///
		  MaxTerm = vNumber.operator long();
		  //////////////////////////////////////////////////////////////////////
		  bState = TRUE;
		}
	}
	else
	{
		AfxMessageBox("FAIL WITH DB IN PROCESSING QUERY- TermValue");
		bState = TRUE;
	}
	hr = Rs->Close();
//////////////////////////// Getting Min, Max of Doc Num ////////////////////
	strcpy(szQuery, 
		"SELECT MIN(DocNumber) AS [DMinNum], MAX(DocNumber) AS [DMaxNum] FROM TDocumentInfo");
	hr = Rs->Open(szQuery, _variant_t((IDispatch *) pConnection, TRUE),
				ADODB::adOpenStatic,
				ADODB::adLockReadOnly,
				-1 );
	if (!hr)
	{
		if(Rs->BOF)
		{
			::MessageBox( NULL, "No records,NO TermInfo, some thing wrong in the db", "", MB_OK );
			bState = FALSE;
		}
		else
		{ /////// binding the values from the table to ARSDocument. class //////
		  vNumber = Rs->GetCollect("DMinNum");
		  ///// here i will pass the pervious variants to the caller///
		  MinDoc = vNumber.operator long();
		  vNumber = Rs->GetCollect("DMaxNum");
		  MaxDoc = vNumber.operator long();
		  //////////////////////////////////////////////////////////////////////
		  bState = TRUE;
		}
	}
	else
	{
		AfxMessageBox("FAIL WITH DB IN PROCESSING QUERY- TermValue");
		bState = TRUE;
	}
	hr = Rs->Close();
	return bState;
}
