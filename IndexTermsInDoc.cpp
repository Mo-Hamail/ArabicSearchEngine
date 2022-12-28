// IndexTermsInDoc.cpp: implementation of the CIndexTermsInDoc class.
// 
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ARS.h"
#include "IR.h"
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

extern CDBManpulation		ARSdb;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIndexTermsInDoc::CIndexTermsInDoc()
{

}

CIndexTermsInDoc::~CIndexTermsInDoc()
{

}

void CIndexTermsInDoc::SetIndexTermInfo(LONG TermNum, LONG DocNum, double Weight, int DFi)
{
	m_TermNum = TermNum;
	m_DocNum  = DocNum ;
	m_Weight  = Weight ;
	m_DFi	  = DFi	  ;
}

LONG CIndexTermsInDoc::GetDocNum()
{
	return m_DocNum;
}

LONG CIndexTermsInDoc::GetTermNum()
{
	return m_TermNum;
}

double CIndexTermsInDoc::GetWeight()
{
	return m_Weight;
}

int CIndexTermsInDoc::GetFrequency()
{
	return m_DFi;
}

void CIndexTermsInDoc::ConstructTermDocMat(int nCollection, mwArray &TMmat)
{
	if( !ARSdb.GetDocTermInfo() )
	{
		AfxMessageBox("Couldn't access the ARSdb");
		::exit(1);
	}
	ARSdb.FillArray(TMmat);
}
