// Query.cpp: implementation of the CQuery class.
//
//////////////////////////////////////////////////////////////////////
 
#include "stdafx.h"
#include "ARS.h"
#include "KeyWord.h"
#include "ARSDocument.h"
#include "IndexTermsInDoc.h"
#include "FilePrepare.h"
#include "DBManpulation.h"
#include "Indexer.h"
#include "Query.h"
#include "SearchEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CDBManpulation		ARSdb;
extern CFilePrepare			fpDocs;
extern CSearchEngine		ARSsearcher;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CQuery::CQuery()
{
	
}

CQuery::~CQuery()
{
	delete [] SimDocList;
	delete [] SimTermList;
}

BOOL CQuery::ProcessQuery(char* QueryValue, BOOL bSearchType)
{
	char*	token;
	BOOL	bState = TRUE, bEmpty = TRUE;
	LONG	Index;
	double* QueryVector = new double[ARSdb.MaxTerm+1];
	if(QueryVector == NULL)
	{
		AfxMessageBox("FAIL WITH Allocating DocVector");
		exit(0);
	}
	memset( QueryVector, 0, (ARSdb.MaxTerm+1)*8);

	token = ::strtok(QueryValue, (char*)fpDocs.seps);
	while(token != NULL && strlen(token) > 14)
		token = ::strtok(NULL, (char*)fpDocs.seps);
	while(token != NULL)
	{
		if( !ARSdb.MatchCommonWord(token) ) 
		{ // if the token not in the StopList do ...
			if( ARSdb.GetTermInfoByName(token, Index) )
			{
				bEmpty = FALSE;
				QueryVector[Index-1] = 1;
			}
		}
		do{
			token = ::strtok(NULL, (char*)fpDocs.seps);
		}
		while(token != NULL && strlen(token) > 14);
	}
	if(!bEmpty)
	{// Query_hh now is Qtransposed, because the of passing data 
		Query_hh = mwArray(1,ARSdb.MaxTerm, QueryVector);
		//Query_hh = //m_V(223, colon())+ 
		//	m_V(498, colon());
		FoldInQuery();		
		//SimDocList[0].nItem = -1;
		//SimTermList[0].nItem = -1;

		if(bSearchType == 0)
		{
			bState = ARSsearcher.FindSimilarDoc(SimDocList, m_V);
		}
		else
		{
			if(bSearchType == 1)
			{
				bState = ARSsearcher.FindSimilarTerm(SimTermList, m_U);		
			}
			else
			{
				bState = ARSsearcher.FindSimilarDoc(SimDocList, m_V);
				bState = ARSsearcher.FindSimilarTerm(SimTermList, m_U);		
			}
		}
	}
	else 
	{
		AfxMessageBox("Query is out of domain to document collection");
		bState =  FALSE;
	}
	delete[] QueryVector;
	return bState;
}

BOOL CQuery::FoldInQuery()
{
	BOOL bState = TRUE;
	Query_hh = Query_hh * mwScaleofTerms;
	
	return bState;
}

void CQuery::DoScaleofTerms()
{
	mwScaleofTerms = m_U * inv(m_S);
}
