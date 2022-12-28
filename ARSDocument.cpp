// ARSDocument.cpp: implementation of the CARSDocument class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IR.h"
#include "ARS.h" 
#include "KeyWord.h"
#include "ARSDocument.h"
#include "IndexTermsInDoc.h"
#include "FilePrepare.h"
#include "DBManpulation.h"
#include "Indexer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//////////////////Defintion of the STATIC Members in file Scope///////
int CARSDocument::nTotalDocs ;
//CMapStringToOb CARSDocument::WordDFiCollection;
//CMapStringToOb CARSDocument::WordCountCollection;
///////////////////////////////////////////////////////////////////////
extern CDBManpulation	ARSdb;
extern CIndexer			ARSIndexer;
extern CKeyWord			ARSKWords;
//////////////////////////////////////////////////////////////////////
CFilePrepare	fpDocs;

IMPLEMENT_DYNAMIC( WordCountStruct, CObject )
IMPLEMENT_DYNAMIC( WordDFI_Struct, CObject )
IMPLEMENT_DYNAMIC( WordStruct, CObject )
CARSDocument::CARSDocument()
{

}

CARSDocument::~CARSDocument()
{

}

BOOL CARSDocument::PrepareDocument(CStringList* DocPathList)
{
	WordDFiCollection.RemoveAll();
	nTotalDocs = 0;
	CString		sCurrentDoc;
	ARSdb.AddNewDoc(DocPathList); // for recording documents that been processed 
									// in the ARS database ...
	for(POSITION pos = DocPathList->GetHeadPosition(); pos != NULL;)
	{
		sCurrentDoc = DocPathList->GetNext(pos);
		CountFreq(sCurrentDoc);
	}
	CalculateWeight(DocPathList);
	return TRUE;
}
void CARSDocument::CountFreq(CString DocPath)
{
	WordCountStruct*	pWC;
	WordDFI_Struct*		pWD;
	WordStruct*			pWS;
	char *				token;
	CMapStringToOb		WordUpdateList;
	CMapStringToOb		WordCountCollection;

	
	WordCountCollection.RemoveAll(); // for every collection of documents ...

	if( fpDocs.OpenFile(DocPath.GetBuffer(DocPath.GetLength())) )
	{
		token = ::strtok(fpDocs.pFileContent, (char*)fpDocs.seps);
		while(token != NULL && strlen(token) > 14)
			token = ::strtok(NULL, (char*)fpDocs.seps);
		while(token != NULL)
		{
			 // check if word found increment Frequency and nDFi 
				//  else add it in word map put 1 in Frequency and nDFi++
				// take care of not resetting nDFi, only Frequency...
			if( !ARSdb.MatchCommonWord(token) ) 
			{ // if the token not in the StopList do ...
				if(WordCountCollection.Lookup((const char*)token, ( CObject*& )pWC))
				{
					WordCountCollection.SetAt(pWC->WordValue, new WordCountStruct(++pWC->Frequency, pWC->WordValue));
					delete pWC;
				}
				else
				{
					WordCountCollection.SetAt((const char*)token, new WordCountStruct(1, (char*)token));
				}
				if( !WordUpdateList.Lookup((const char*)token, ( CObject*& )pWS) )
					WordUpdateList.SetAt((const char*)token, new WordStruct((char*)token));
			}
			do{
				token = ::strtok(NULL, (char*)fpDocs.seps);
			}
			while(token != NULL && strlen(token) > 14);
		}
		nTotalDocs++;
		{ // this block for updating the DFI of the words extracted from current doc. ...
			CString				key;
			for(POSITION pos = WordUpdateList.GetStartPosition();pos!=NULL;)
			{
				WordUpdateList.GetNextAssoc( pos, key, (CObject*&)pWS);
				WordCountCollection.Lookup((const char*)pWS->WordValue, ( CObject*& )pWC);
				if( WordDFiCollection.Lookup((const char*)pWS->WordValue, ( CObject*& )pWD) )
				{
					WordDFiCollection.SetAt((const char*)pWS->WordValue, new WordDFI_Struct(++pWD->nDFi, pWC->Frequency + pWD->nGFi, (char*)pWD->WordValue,0,0,FALSE));
					delete pWD;					
				}
				else
				{
					WordDFiCollection.SetAt((const char*)pWS->WordValue, new WordDFI_Struct(1, pWC->Frequency,(char*)pWS->WordValue, 0,0,FALSE));
				}				
			}			
		}//////////////////////////////////////////////////////////////////////////////////
/*//////////////////////////////////////////////////////////////////////*/
		{ // block for writing results of WordCountCollection for the current Doc ...
			WordCountStruct*	pWC1;
			CString				key;
			char 				strLine[80];
			sprintf(strLine,"C:\\temp\\%d.txt",nTotalDocs);
			CStdioFile	constfile( strLine, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
			//int CollectionCount = WordCountCollection.GetCount();
			for(POSITION pos = WordCountCollection.GetStartPosition();pos!=NULL;)
			{
				WordCountCollection.GetNextAssoc( pos,key , (CObject*&)pWC1);
				sprintf(strLine,"%d-%s\r", pWC1->Frequency, pWC1->WordValue);
				constfile.Write(strLine, 80);
				WordCountCollection.RemoveKey(key);
				delete pWC1;
			}
			constfile.Close();
		}
/*///////////////////////////////////////////////////////////////////////*/
	}
	else
	{
		AfxMessageBox( "Error, Couldn't open file" );
	}
/*//////////////////////////////////////////////////////////////////////*/
/*
	{ // block for testing the output data from every phase 
		WordCountStruct*	pWC1;
		CString				key;
		CStdioFile	constfile("_testToken.txt", CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		char 		strLine[80];
		
		//int CollectionCount = WordCountCollection.GetCount();
		for(POSITION pos = WordCountCollection.GetStartPosition();pos!=NULL;)
		{
			WordCountCollection.GetNextAssoc( pos, key, (CObject*&)pWC1);
			wsprintf(strLine,"%s\t%d\n",pWC1->WordValue, pWC1->Frequency);
			constfile.WriteString (strLine);
		}
		constfile.Close();
	}
/*///////////////////////////////////////////////////////////////////////*/
/*//////////////////////////////////////////////////////////////////////*/
/*
	{ // block for testing the output data from DFI
		WordDFI_Struct*		pWD1;
		CString				key;
		CStdioFile	constfile("_testDFI.txt", CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		char 		strLine[80];
		
		//int CollectionCount = WordCountCollection.GetCount();
		for(POSITION pos = WordDFiCollection.GetStartPosition();pos!=NULL;)
		{
			WordDFiCollection.GetNextAssoc( pos, key, (CObject*&)pWD1);
			wsprintf(strLine,"%s\t%d\t%d\n",pWD1->WordValue, pWD1->nGFi,pWD1->nDFi);
			constfile.WriteString (strLine);
		}
		constfile.Close();
	}	
/*///////////////////////////////////////////////////////////////////////*/
	///////////////////////////////// Avoiding memory leak ///////////////
	{
		CString				key;
		for(POSITION pos = WordUpdateList.GetStartPosition();pos!=NULL;)
		{
			WordUpdateList.GetNextAssoc( pos,key , (CObject*&)pWS);
			WordUpdateList.RemoveKey(key);
			delete pWS;
		}
	}
////////////////////////////////////////////////////////////////////////
	//WordUpdateList.RemoveAll();
} //end of CountFreq()

void CARSDocument::CalculateWeight(CStringList* DocPathList)
{
	char 				strLine[80];
	WordCountStruct		WC;
	WordDFI_Struct*		pWD;
	CStdioFile			constfile;
	double				fPGiVal;
	long				lTnum;
	CIndexTermsInDoc	ARSIndexTerm;

	for(int nFileNum = 1; nFileNum <= nTotalDocs; nFileNum++)
	{ // this Iteration on files for calculating the partial Global weight ...
		sprintf(strLine,"C:\\temp\\%d.txt",nFileNum);
		constfile.Open( strLine, CFile::modeRead | CFile::typeText);
		//strLine = NULL;

		while( constfile.Read( strLine, 80 ) )
		{
			sscanf(strLine,"%d-%s\r", &WC.Frequency, &WC.WordValue);
			if( WordDFiCollection.Lookup((const char*)&WC.WordValue, ( CObject*& )pWD) )
			{
				fPGiVal = ((double)WC.Frequency/pWD->nGFi) * ( (log10((double)WC.Frequency/pWD->nGFi)/log10(2)) );
				WordDFiCollection.SetAt((const char*)pWD->WordValue, new WordDFI_Struct(pWD->nDFi, pWD->nGFi, (char*)pWD->WordValue, pWD->fPGi + fPGiVal,0,FALSE) );
				delete pWD;
			}
		}
		constfile.Close();
	}
	double fLw, fGw, fWeight;
	CString	sCurrentDoc;
	CARSDocument	dCurrentDocInfo;
	double			fWThreshold = ARSIndexer.GetThreShold();
//**/CStdioFile	constfile1("_Weights274.txt", CFile::modeCreate | CFile::modeWrite | CFile::typeText);
//////////// here get the real document # from Document Table ////////
	POSITION pos;
	for(pos = DocPathList->GetHeadPosition(),nFileNum = 1; pos != NULL;nFileNum++)
	{
		sCurrentDoc = DocPathList->GetNext(pos);
		ARSdb.GetDocumentInfoByName( sCurrentDoc.GetBuffer(sCurrentDoc.GetLength()), dCurrentDocInfo );
		// this Iteration on files for calculating the weight of the term ...
		sprintf(strLine,"C:\\temp\\%d.txt",nFileNum);
		constfile.Open( strLine, CFile::modeRead | CFile::typeBinary);
		//strLine = NULL;
		while( constfile.Read( strLine, 80 ) )
		{
			sscanf(strLine,"%d-%s", &WC.Frequency, &WC.WordValue);
//			if(!strcmp(WC.WordValue, "ÅÌãÇáí"))
//				int xx = 0;
			if( WordDFiCollection.Lookup((const char*)&WC.WordValue, ( CObject*& )pWD) )
			{
				fLw = ( log10(WC.Frequency + 1)/ log10(2) );
				fGw = 1 - ( pWD->fPGi/( log10(nTotalDocs)/log10(2) ) );
				fWeight = fLw * fGw;
				if( fWeight > fWThreshold )
				{
				// here add the pWD->WordValue and fGw to KeyWord Table ...
					if(!pWD->bMarked)
					{
						//pWD->bMarked = 1;						
						strcpy(ARSKWords.m_TermValue, WC.WordValue);
						ARSKWords.m_GlobalWeight = float(fGw);
						ARSKWords.m_Gfi			 = pWD->nGFi;
						ARSdb.AddNewTerm(ARSKWords);
						if(!ARSdb.GetTermInfoByName(pWD->WordValue, lTnum))
							::MessageBox( NULL, "No records,NO TermInfo, some thing wrong in the db", "", MB_OK );
						WordDFiCollection.SetAt(
							(const char*)pWD->WordValue,
							new WordDFI_Struct(pWD->nDFi, pWD->nGFi, (char*)pWD->WordValue, pWD->fPGi, lTnum, TRUE) 
							);
						delete pWD;
						if( !WordDFiCollection.Lookup((const char*)&WC.WordValue, ( CObject*& )pWD) )
							AfxMessageBox("ERROR in processing Terms(bMarked)");
					}
					if(!pWD->TNum)
						AfxMessageBox("ERROR in processing Terms");
					ARSIndexTerm.SetIndexTermInfo(pWD->TNum, 
												dCurrentDocInfo.m_DocNumber,
												fWeight,
												WC.Frequency);
					ARSdb.AddIndexTerm(ARSIndexTerm);
/*//////////////////////////////////////////////////////////////////////*/			
/*				// block for testing the output data from every phase 
				char 		strLine[80];				
				sprintf(strLine,"%s,%d%f,%f,%f\n",pWD->WordValue, pWD->TNum, fLw, fGw, fWeight);
				constfile1.WriteString (strLine);
/*///////////////////////////////////////////////////////////////////////*/	
///////////////////////////////////////////////////////////////////////////////
				}
			}
		}
		constfile.Close();
	}
/////////////////////////////////////////////////////////////////////
////////////////////////old block have been updated above ///////////
/*	for(nFileNum = 1; nFileNum <= nTotalDocs; nFileNum++)
	{ // this Iteration on files for calculating the weight of the term ...
		sprintf(strLine,"C:\\temp\\%d.txt",nFileNum);
		constfile.Open( strLine, CFile::modeRead | CFile::typeBinary);
		//strLine = NULL;
		while( constfile.Read( strLine, 80 ) )
		{
			sscanf(strLine,"%d-%s", &WC.Frequency, &WC.WordValue);
//			if(!strcmp(WC.WordValue, "ÅÌãÇáí"))
//				int xx = 0;
			if( WordDFiCollection.Lookup((const char*)&WC.WordValue, ( CObject*& )pWD) )
			{
				fLw = ( log10(WC.Frequency + 1)/ log10(2) );
				fGw = 1 - ( pWD->fPGi/( log10(nTotalDocs)/log10(2) ) );
				fWeight = fLw * fGw;
				if( fWeight >= ARSIndexer.GetThreShold() )
				{
				// here add the pWD->WordValue and fGw to KeyWord Table ...

///////////////////////////////////////////////////////////////////////////////
				}
/*//////////////////////////////////////////////////////////////////////*/			
/*				// block for testing the output data from every phase 
				char 		strLine[80];				
				sprintf(strLine,"%s,%f,%f,%f\n",WC.WordValue, fLw, fGw, fWeight);
				constfile1.WriteString (strLine);
/*///////////////////////////////////////////////////////////////////////*/				
/*			}
		}
		constfile.Close();
	}
/**///constfile1.Close();
/////////////////////////////////////end of old block /////////////
///////////////////////////////// Avoiding memory leak ///////////////
	{
		CString				key;
		for(POSITION pos = WordDFiCollection.GetStartPosition();pos!=NULL;)
		{
			WordDFiCollection.GetNextAssoc( pos,key , (CObject*&)pWD);
			WordDFiCollection.RemoveKey(key);
			delete pWD;
		}
	}
/////////////////////////////////////////////////////////////////////////
}// end of CaluclateWeight()

WordCountStruct::WordCountStruct()
{
}
WordCountStruct::WordCountStruct(int Freq , char* WVlaue)
{
	Frequency = Freq;
	strcpy(WordValue, WVlaue);
}
WordCountStruct::~WordCountStruct()
{
}

WordDFI_Struct::WordDFI_Struct()
{
}
WordDFI_Struct::WordDFI_Struct(int nFreq, int nGFreq, char *WordVal, double fPGiVal=0, long lTnum = 0, BOOL bMark = FALSE)
{
	nDFi = nFreq;
	nGFi = nGFreq;
	fPGi = fPGiVal;
	strcpy(WordValue, WordVal);
	bMarked = bMark;
	TNum	= lTnum;
}
WordDFI_Struct::~WordDFI_Struct()
{
}
WordStruct::WordStruct()
{
}
WordStruct::WordStruct(char* WVlaue)
{
	strcpy(WordValue, WVlaue);
}
WordStruct::~WordStruct()
{
}


BOOL CARSDocument::SetIgnored(BOOL bIgnored, int DocNum)
{
	return ARSdb.UpdateDoc(bIgnored, DocNum);
}

BOOL CARSDocument::ReSetIgnored(BOOL bIgnored, int DocNum)
{
	return ARSdb.UpdateDoc(bIgnored, DocNum);
}
