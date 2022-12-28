// SVD.cpp: implementation of the CSVD class.
// 
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ARS.h"
#include "SVD.h"
#include "IR.h"
#include "KeyWord.h"
#include "ARSDocument.h"
#include "IndexTermsInDoc.h"
#include "FilePrepare.h"
#include "DBManpulation.h"
#include "Indexer.h"
#include "fstream.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
mwArray CSVD::m_V;
mwArray CSVD::m_U;
mwArray CSVD::m_S;

//////////////////////////////////////////////////////////////////////
extern CARSDocument		ArabicDocs;
extern CIndexer			ARSIndexer;
//////////////////////////////////////////////////////////////////////
CSVD::CSVD()
{

}
CSVD::CSVD(int MaxVal)
{
	nMaxFactors = MaxVal;
}
CSVD::~CSVD()
{

}

BOOL CSVD::DoIndexing(CStringList *DocPathList)
{
	BOOL bState = TRUE;
	ConstructDocBase(DocPathList);
//	ArabicDocs.PrepareDocument( DocPathList );
	mwArray A = ARSIndexer.GetTermDocMat();
	A = sparse(A);
	save("C:\\My Documents\\my corpus\\economic\\A.mat", "A", A);
/**/	//save("C:\\My Documents\\test10\\A10.mat", "A10", A);
	CalculateSVD(A);
	WriteSVD();
	
	return bState;
}

int CSVD::GetMaxFactors()
{
	return nMaxFactors;
}

void CSVD::SetMaxFactors(int MaxVal)
{
	nMaxFactors = MaxVal;
}



BOOL CSVD::CalculateSVD(mwArray &A)
{
	m_U = svds(&m_S, &m_V, A, nMaxFactors);
	return TRUE;
}

BOOL CSVD::WriteSVD()
{	
 /**/   try 
	{   // Save (and name) the SVD components U,V,S.
        save("C:\\My Documents\\my corpus\\economic\\U.mat", "U", m_U);
		save("C:\\My Documents\\my corpus\\economic\\V.mat", "V", m_V);
        save("C:\\My Documents\\my corpus\\economic\\S.mat", "S", m_S);
//		save("C:\\My Documents\\test10\\U10.mat", "U10", m_U);
//		save("C:\\My Documents\\test10\\V10.mat", "V10", m_V);    
//		save("C:\\My Documents\\test10\\S10.mat", "S10", m_S);
	}
    catch ( mwException &ex ) 
	{	////////out file for exploring the write error ...///
		AfxMessageBox("FAIL WITH saving U, V, S");
		ofstream out_file("_writerr.txt", ios::out);
		out_file << ex << ends;
		out_file.close();
		/////////////////////////////////////////////// .............///
		AfxMessageBox("FAIL WITH writing U file,V file, S file ");
		return FALSE;
    }
////////////out file for exploring the U ...///
/*	ofstream out_file("_U.txt", ios::out);
	out_file << m_U << ends;
	out_file.close();
/////////////////////////////////////////////////// .............///*/
   return TRUE;
}

mwArray& CSVD::GetV()
{
	load("C:\\My Documents\\my corpus\\economic\\V.mat", "V", &m_V);
	return m_V;
}

mwArray& CSVD::GetU()
{
	load("C:\\My Documents\\my corpus\\economic\\U.mat", "U", &m_U);
	return m_U;
}

mwArray& CSVD::GetS()
{
	load("C:\\My Documents\\my corpus\\economic\\S.mat", "S", &m_S);
	return m_S;
}

BOOL CSVD::ConstructDocBase(CStringList *DocPathList)
{
	BOOL			bState = TRUE;
	CARSDocument	DocBase;
	DocBase.PrepareDocument( DocPathList );
	return bState;
}
