// DBManpulation.h: interface for the CDBManpulation class.
// 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBMANPULATION_H__3DB71F32_C05A_4B25_9916_CC4A0A72D3BA__INCLUDED_)
#define AFX_DBMANPULATION_H__3DB71F32_C05A_4B25_9916_CC4A0A72D3BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDBManpulation  
{
	/////////operations
public:
	CDBManpulation();
	virtual ~CDBManpulation(); 
	BOOL OpenConnection(void);
	void CloseConnection();
	BOOL MatchCommonWord(char*  szWordValue);

	/////////attributes
private:
	void DtoString(float dValue, char* sValue);	
	HRESULT					 hr;
public:
	BOOL GetDocTermInfo();
	void FillArray(mwArray& TMmat);
	BOOL UpdateDoc(BOOL, int);
	BOOL AddIndexTerm(CIndexTermsInDoc TermDocInfo);
	BOOL GetTermInfoByNum(LONG TNum, char* TVal);
	BOOL GetTermInfoByName(char*, LONG&);
	BOOL AddNewTerm(CKeyWord);
	BOOL CheckDocBase();
	BOOL GetDocumentInfoByNumber(int, CARSDocument& );
	BOOL GetDocumentInfoByName(char*, CARSDocument& );
	BOOL AddNewDoc(CStringList *);
	ADODB::_RecordsetPtr     Rs;
	ADODB::_ConnectionPtr    pConnection;
	BOOL LoadCommonWords();
	LONG MaxTerm;
	LONG MaxDoc;
	LONG MinDoc;

protected:
	CMapStringToOb CommonWordCollection;
};
#endif // !defined(AFX_DBMANPULATION_H__3DB71F32_C05A_4B25_9916_CC4A0A72D3BA__INCLUDED_)
