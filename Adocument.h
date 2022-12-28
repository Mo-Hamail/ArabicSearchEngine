// Adocument.h: interface for the CAdocument class.
// 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ADOCUMENT_H__1D080877_7CBF_4982_9971_18009004AD56__INCLUDED_)
#define AFX_ADOCUMENT_H__1D080877_7CBF_4982_9971_18009004AD56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
///////////////////////////////////Data structure needed for processing ////
struct WordCountStruct
{
	char	WordValue[15];
	int		Frequency;
public:
	WordCountStruct(int Freq, char* WVlaue);
};
////////////////////////////////////////////////////////////////////////////

class CAdocument  
{
public:
	CAdocument();
	virtual ~CAdocument();
private: // attributes
	char			  m_szLocation[129];
	char			  m_szID[50];
	WordCountStruct   WordCount;
	char		      m_szType[4];
	BOOL              m_bIgnored;
};

#endif // !defined(AFX_ADOCUMENT_H__1D080877_7CBF_4982_9971_18009004AD56__INCLUDED_)
