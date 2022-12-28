// CommonWord.h: interface for the CCommonWord class.
// 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMONWORD_H__567295EB_FA40_41FB_A834_8E225134AA83__INCLUDED_)
#define AFX_COMMONWORD_H__567295EB_FA40_41FB_A834_8E225134AA83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCommonWord  
{
public:
	CCommonWord();
	virtual ~CCommonWord();
	
private:
	char  szWordValue[12];
public:
	BOOL IsWordCommon(char* pMatchWord);
	void AddCommonWord(char* pNewWord);

};

#endif // !defined(AFX_COMMONWORD_H__567295EB_FA40_41FB_A834_8E225134AA83__INCLUDED_)