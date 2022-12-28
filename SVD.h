// SVD.h: interface for the CSVD class.
// 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVD_H__1A339C9A_7027_4EDA_AA06_7B30867E7A26__INCLUDED_)
#define AFX_SVD_H__1A339C9A_7027_4EDA_AA06_7B30867E7A26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LSI.h"

class CSVD : virtual public CLSI  
{
public:
	mwArray& GetS();
	mwArray& GetU();
	mwArray & GetV();
	CSVD(int  MaxVal);
	void SetMaxFactors(int MaxVal);
	int GetMaxFactors();
	BOOL DoIndexing(CStringList* DocPathList);
	CSVD();
	virtual ~CSVD();

protected:
	BOOL ConstructDocBase(CStringList * DocPathList);
	BOOL WriteSVD();
	BOOL CalculateSVD(mwArray &A);
	int nMaxFactors;
	static mwArray m_V;
	static mwArray m_U;
	static mwArray m_S;
};

#endif // !defined(AFX_SVD_H__1A339C9A_7027_4EDA_AA06_7B30867E7A26__INCLUDED_)
