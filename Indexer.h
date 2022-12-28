// Indexer.h: interface for the CIndexer class.
// 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INDEXER_H__0DAC23A5_8894_4B20_9B72_014D88F722C6__INCLUDED_)
#define AFX_INDEXER_H__0DAC23A5_8894_4B20_9B72_014D88F722C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIndexer : virtual public CIR 
{
public:
	mwArray&  GetTermDocMat();
	double GetThreShold();
	void SetThreShold(double ThreSholdVal);
	BOOL CheckDocTermBase();
	CIndexer();
	virtual ~CIndexer();

protected:
	double WeightThreshold;
private:
	mwArray mwTermDocMat;
};

#endif // !defined(AFX_INDEXER_H__0DAC23A5_8894_4B20_9B72_014D88F722C6__INCLUDED_)
