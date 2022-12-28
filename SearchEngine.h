// SearchEngine.h: interface for the CSearchEngine class.
// 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEARCHENGINE_H__C5952CCB_1EF0_40BA_8F9F_F8CAFA48D008__INCLUDED_)
#define AFX_SEARCHENGINE_H__C5952CCB_1EF0_40BA_8F9F_F8CAFA48D008__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IR.h"

int compare( const void *arg1, const void *arg2 );

class CSearchEngine : virtual public CIR  
{
public:
	int GetSearchLimit();
	double GetSimilarity();
	void SetSearchLimit(int nLimitValue);
	void SetSimilarity(float SimValue);
	BOOL FindSimilarTerm(ItemList* SimTermList, mwArray& Uk);
	BOOL FindSimilarDoc(ItemList* SimDocList, mwArray& Vk);
	CSearchEngine();
	virtual ~CSearchEngine();

protected:
	double CosineMeasure(const mwArray &Q_hh, const mwArray &VU);
	int nSearchLimit;
	double fSimValue;
};

#endif // !defined(AFX_SEARCHENGINE_H__C5952CCB_1EF0_40BA_8F9F_F8CAFA48D008__INCLUDED_)
