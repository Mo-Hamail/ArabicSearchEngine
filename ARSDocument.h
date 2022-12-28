// ARSDocument.h: interface for the CARSDocument class.
// 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARSDOCUMENT_H__BDB3D937_F1F8_482F_A690_A3EE09F1FF14__INCLUDED_)
#define AFX_ARSDOCUMENT_H__BDB3D937_F1F8_482F_A690_A3EE09F1FF14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ir.h"
class WordCountStruct : public CObject
{
	DECLARE_DYNAMIC( WordCountStruct )
public:
	char	WordValue[15];
	int		Frequency;
public:
	WordCountStruct();
	WordCountStruct(int Freq, char* WVlaue);
	virtual ~WordCountStruct();
//	void Serialize( CArchive& ar);
//	void AssertValid() const;
 #ifdef _DEBUG
    void Dump( CDumpContext& dc ) const
    {
        CObject::Dump( dc );
        dc << WordValue;
    }
 #endif

};
class WordDFI_Struct : public CObject
{
	DECLARE_DYNAMIC( WordDFI_Struct )
public:
	char	WordValue[15];
	int		nDFi;
	int		nGFi;
	double	fPGi;
	BOOL	bMarked;
	LONG	TNum;
public:
	
	WordDFI_Struct();
	WordDFI_Struct(int, int, char*, double, long, BOOL);
	virtual ~WordDFI_Struct();
	//	void Serialize( CArchive& ar);
//	void AssertValid() const;
 #ifdef _DEBUG
    void Dump( CDumpContext& dc ) const
    {
        CObject::Dump( dc );
        dc << WordValue;
    }
 #endif
};
class WordStruct : public CObject
{
	DECLARE_DYNAMIC( WordStruct )
public:
	char	WordValue[15];
public:
	WordStruct();
	WordStruct(char* WVlaue);
	virtual ~WordStruct();
//	void Serialize( CArchive& ar);
//	void AssertValid() const;
 #ifdef _DEBUG
    void Dump( CDumpContext& dc ) const
    {
        CObject::Dump( dc );
        dc << WordValue;
    }
 #endif

};
struct WordWeight_Struct{
	char	WordValue[15];
	double	Weight;
	BOOL	Representative;
};
class CARSDocument : virtual public CIR  
{
public:
	BOOL ReSetIgnored(BOOL bIgnored, int DocNum);
	BOOL SetIgnored(BOOL bIgnored, int DocNum);
	BOOL m_Ignored;
	char m_Type[5];
	LONG m_DocNumber;
	char m_Location[256];
	char m_DocID[50];
	BOOL PrepareDocument( CStringList* );
	CARSDocument();
	virtual ~CARSDocument();

protected:
	void CalculateWeight(CStringList*);
	void CountFreq(CString DocPath);
private:
	static int nTotalDocs;					  // Declaration of the static member
//	static CMapStringToOb WordDFiCollection;  // Declaration of the static member
//	static CMapStringToOb WordCountCollection;// Declaration of the static member
	CMapStringToOb WordDFiCollection;  // Declaration of the static member
	//CMapStringToOb WordCountCollection;// Declaration of the static member
};

#endif // !defined(AFX_ARSDOCUMENT_H__BDB3D937_F1F8_482F_A690_A3EE09F1FF14__INCLUDED_)
