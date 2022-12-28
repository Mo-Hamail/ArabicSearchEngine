// SVDDel.h: interface for the CSVDDel class.
// 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVDDEL_H__81AC11B0_5DFF_4BF9_BC94_305CA496B4F0__INCLUDED_)
#define AFX_SVDDEL_H__81AC11B0_5DFF_4BF9_BC94_305CA496B4F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SVD.h"

class CSVDDel : virtual public CSVD  
{
public:
	BOOL MarkDocAsDel(CString sCurrentFile);
	BOOL FoldOutDoc(CStringList& FilesPathList);
	CSVDDel();
	virtual ~CSVDDel();

};

#endif // !defined(AFX_SVDDEL_H__81AC11B0_5DFF_4BF9_BC94_305CA496B4F0__INCLUDED_)
