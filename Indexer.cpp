// Indexer.cpp: implementation of the CIndexer class.
// 
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IR.h"
#include "ARSDocument.h"
#include "KeyWord.h"
#include "ARS.h"
#include "Indexer.h"
#include "IndexTermsInDoc.h"
#include "DBManpulation.h"
#include "fstream.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern CDBManpulation	ARSdb;
extern CIndexTermsInDoc	ARSITerms;

CIndexer::CIndexer()
{
/**/	WeightThreshold = 2.74;
}

CIndexer::~CIndexer()
{

}

BOOL CIndexer::CheckDocTermBase()
{
	return ARSdb.CheckDocBase();	
}

void CIndexer::SetThreShold(double ThreSholdVal)
{
	WeightThreshold = ThreSholdVal;
}

double CIndexer::GetThreShold()
{
	return  WeightThreshold;
}

mwArray& CIndexer::GetTermDocMat()
{
	ARSITerms.ConstructTermDocMat(1, mwTermDocMat);
	return mwTermDocMat;
}
