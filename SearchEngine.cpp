// SearchEngine.cpp: implementation of the CSearchEngine class.
// 
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ARS.h"
#include "ARSDocument.h"
#include "KeyWord.h"
#include "IndexTermsInDoc.h"
#include "DBManpulation.h"
#include "CommonWord.h"
#include "Indexer.h"
#include "SVD.h"
#include "SVDDel.h"
#include "Query.h"
#include "SearchEngine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CSVD				ARSsvd;
extern CQuery			ARSquery;
extern CDBManpulation	ARSdb;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSearchEngine::CSearchEngine()
{

}

CSearchEngine::~CSearchEngine()
{

}

BOOL CSearchEngine::FindSimilarDoc(ItemList* SimDocList, mwArray& Vk)
{
	double	fResultSim = 0;
	int		DocNum,Index = 0;
	memset( SimDocList, -1, (ARSdb.MaxDoc+1) * sizeof(ItemList) );
	for(DocNum = 1; DocNum <= ARSdb.MaxDoc; DocNum++)
	{

		fResultSim = CosineMeasure( ARSquery.Query_hh, Vk(DocNum, colon()) );
		if( fResultSim >= fSimValue )
		{
			SimDocList[Index].nItem = DocNum;
			SimDocList[Index].fSim  = fResultSim;
			Index++;
		}
	}
	if(!Index)
		AfxMessageBox("·„ Ì „ «·⁄ÀÊ— ⁄·Ï ÊÀ«∆ﬁ  ‘«»Â «·≈” ›”«— „⁄ ‰”»… «· ‘«»Â «·„Õœœ… ›Ï «·≈” ›”«—");
		//::MessageBox(NULL, "could not find any similar documents","", MB_OK );
	else
		qsort( (void *)SimDocList, (size_t)Index, sizeof( ItemList ), compare );
///////////////////////////////////////////////////////////////////////////////////
/*
	{ // block for testing the output data from every phase 
		CStdioFile	constfile("_sortdoc.txt", CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		char 		strLine[80];
		
		//int CollectionCount = WordCountCollection.GetCount();
		for(int i = 0;i<Index;i++)
		{
			double x = SimDocList[i].fSim;
			sprintf(strLine,"%d,%f\n",SimDocList[i].nItem, x);
			constfile.WriteString (strLine);
		}
		constfile.Close();
	}
/*///////////////////////////////////////////////////////////////////////*/
	return Index;
}

BOOL CSearchEngine::FindSimilarTerm(ItemList* SimTermList, mwArray& Uk)
{
	double	fResultSim = 0;
	int		TermNum,Index = 0;
	memset( SimTermList, -1, (ARSdb.MaxTerm+1) * sizeof(ItemList) );
	for(TermNum = 1; TermNum <= ARSdb.MaxTerm; TermNum++)
	{
		fResultSim = CosineMeasure( ARSquery.Query_hh, Uk(TermNum, colon()) );
		if( fResultSim >= fSimValue )
		{
			SimTermList[Index].nItem = TermNum;
			SimTermList[Index].fSim  = fResultSim;
			Index++;
		}
	}	
	if(!Index)
		AfxMessageBox("·„ Ì „ «·⁄ÀÊ— ⁄·Ï ﬂ·„«   ‘«»Â «·≈” ›”«— „⁄ ‰”»… «· ‘«»Â «·„Õœœ… ›Ï «·≈” ›”«—");
	else
		qsort( (void *)SimTermList, (size_t)Index, sizeof( ItemList ), compare );
	return Index;
}

void CSearchEngine::SetSimilarity(float SimValue)
{
	fSimValue = SimValue;
}

void CSearchEngine::SetSearchLimit(int nLimitValue)
{
	 nSearchLimit = nLimitValue;
}

double CSearchEngine::GetSimilarity()
{
	return fSimValue;
}

int CSearchEngine::GetSearchLimit()
{
	return nSearchLimit;
}

double CSearchEngine::CosineMeasure(const mwArray &Q_hh, const mwArray &VU)
{
	mwArray res_Arr = ( dot(Q_hh, VU) / (norm(Q_hh) * norm(VU)) );
	double *result = mxGetPr(res_Arr.GetData());
	return (*result);
}

//////////////////////////////////////////////////////////////////////////////
int compare( const void *arg1, const void *arg2 )
{
	ItemList *Item1 = (ItemList*)arg1;
	ItemList *Item2 = (ItemList*)arg2;
	
	if( Item1->fSim > Item2->fSim )
		return -1;
	else
		if( Item1->fSim < Item2->fSim )
			return 1;
		else
			return 0;
}