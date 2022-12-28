// Query.h: interface for the CQuery class.
// 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUERY_H__F0DAE5F5_AF77_44CB_9BEE_3CEF3C06D2E6__INCLUDED_)
#define AFX_QUERY_H__F0DAE5F5_AF77_44CB_9BEE_3CEF3C06D2E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SVD.h"
#include <afxtempl.h>

struct ItemList{
	long   nItem;
	double fSim;
	ItemList(){}
	ItemList(long Num, float simVal){nItem = Num; fSim = simVal;}
};

class CQuery : virtual public CSVD  
{
public:
	void DoScaleofTerms();
	ItemList* SimTermList;
	ItemList* SimDocList;
	mwArray Query_hh;
	BOOL ProcessQuery(char* QueryValue, BOOL bSearchType);
	CQuery();
	virtual ~CQuery();

private:
	BOOL FoldInQuery();
protected:
	mwArray mwScaleofTerms;
};

#endif // !defined(AFX_QUERY_H__F0DAE5F5_AF77_44CB_9BEE_3CEF3C06D2E6__INCLUDED_)
