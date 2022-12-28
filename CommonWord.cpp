// CommonWord.cpp: implementation of the CCommonWord class.
// 
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ARS.h"
#include "CommonWord.h"
#include "ARSDocument.h"
#include "KeyWord.h"
#include "IndexTermsInDoc.h"
#include "DBManpulation.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern 	CDBManpulation	ARSdb;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCommonWord::CCommonWord()
{

}

CCommonWord::~CCommonWord()
{

}
void CCommonWord::AddCommonWord(char *pNewWord)
{
	/////////Add the new word to the Common word table in ARS Database; ////
}

BOOL CCommonWord::IsWordCommon(char *pMatchWord)
{
	///////needing a strategy for matching the input word to words in table //
	char WordValue[15];
	strcpy(WordValue, pMatchWord);
	return ARSdb.MatchCommonWord(WordValue);
}
