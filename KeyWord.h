// KeyWord.h: interface for the CKeyWord class.
//  
////////////////////////////////////////////////////////////////

#if !defined(AFX_KEYWORD_H__D8A7109F_6824_4648_94F1_6281CAB40F6D__INCLUDED_)
#define AFX_KEYWORD_H__D8A7109F_6824_4648_94F1_6281CAB40F6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CKeyWord : virtual public CIR 
{
public:
	long TermID;
	int m_Gfi;
	float m_GlobalWeight;
	char m_TermValue[15];
	CKeyWord();
	virtual ~CKeyWord();

};

#endif // !defined(AFX_KEYWORD_H__D8A7109F_6824_4648_94F1_6281CAB40F6D__INCLUDED_)
