// IndexTermsInDoc.h: interface for the CIndexTermsInDoc class.
// 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INDEXTERMSINDOC_H__5275FF82_5377_4B4A_9EB8_D6E6EA2B08F7__INCLUDED_)
#define AFX_INDEXTERMSINDOC_H__5275FF82_5377_4B4A_9EB8_D6E6EA2B08F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIndexTermsInDoc  
{
public:
	void ConstructTermDocMat(int nCollection, mwArray &TMmat);
	int GetFrequency();
	double GetWeight();
	LONG GetTermNum();
	LONG GetDocNum();
	void SetIndexTermInfo(LONG TermNum, LONG DocNum, double Weight, int DFi);
	CIndexTermsInDoc();
	virtual ~CIndexTermsInDoc();

private:
	int m_DFi;
	double m_Weight;
	LONG m_TermNum;
	LONG m_DocNum;
};

#endif // !defined(AFX_INDEXTERMSINDOC_H__5275FF82_5377_4B4A_9EB8_D6E6EA2B08F7__INCLUDED_)
