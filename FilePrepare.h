// FilePrepare.h: interface for the FilePrepare class.
// 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEPREPARE_H__081901BE_E21E_4381_86FD_172E0878E734__INCLUDED_)
#define AFX_FILEPREPARE_H__081901BE_E21E_4381_86FD_172E0878E734__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
////////////////////////////////////////////////////////////////////////////
typedef struct tagWordInfo
{
	unsigned char cWord[15];
	BOOL bDominantSeparator;
	//BOOL bEndOfSentence; for future use (while using tagged text)

}WORDINFO;
////////////////////////////////////////////////////////////////////////////

class CFilePrepare  
{
private: // properties
	unsigned char map[32];
	int	 nFileLength;
	TEXTMETRIC  tm;

public: // properties
	LPTSTR		pFileContent;
	int			nTokensCount;
	WORDINFO *  TokenInfo;
	WORDINFO *  token;
	unsigned char seps[182]; //126 + 56 latin chars capital and small...

private: // methods
	void DetectInitiales(unsigned char *, unsigned char *);
	void NeedExtraMem(WORDINFO *token, int newCount);
	void SeparatorCoding();

public: // methods
	void FileTokens(void);
	void PrepareTotSize(CSize *sizeTotal);
	void FileDraw(CDC* pDC);
	OpenFile(LPCTSTR  lpszPathName);
	CFilePrepare();
	WORDINFO strtok(unsigned char *string);
	int	GetFileLength() {return nFileLength; }
	virtual ~CFilePrepare();

};

#endif // !defined(AFX_FILEPREPARE_H__081901BE_E21E_4381_86FD_172E0878E734__INCLUDED_)
