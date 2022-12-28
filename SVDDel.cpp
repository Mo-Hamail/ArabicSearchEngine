// SVDDel.cpp: implementation of the CSVDDel class.
// 
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ARS.h"
#include "IR.h"
#include "KeyWord.h"
#include "SVDDel.h"
#include "IndexTermsInDoc.h"
#include "ARSDocument.h"
#include "DBManpulation.h"
#include "Indexer.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
extern CDBManpulation		ARSdb;
extern CARSDocument			ArabicDocs;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSVDDel::CSVDDel()
{

}

CSVDDel::~CSVDDel()
{

}

BOOL CSVDDel::FoldOutDoc(CStringList &FilesPathList)
{
	CString		sCurrentFile;
	for(POSITION pos = FilesPathList.GetHeadPosition(); pos != NULL;)
	{
		sCurrentFile = FilesPathList.GetNext(pos);
		MarkDocAsDel(sCurrentFile);
	}
	return TRUE;
}

BOOL CSVDDel::MarkDocAsDel(CString sCurrentFile)
{
	CARSDocument	TempDoc;
	ARSdb.GetDocumentInfoByName(sCurrentFile.GetBuffer(sCurrentFile.GetLength()),
								TempDoc);
	TempDoc.SetIgnored(TRUE,TempDoc.m_DocNumber);
	return TRUE;
}
