// ARSDoc.h : interface of the CARSDoc class
// 
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARSDOC_H__B1CEA275_F9CB_4E0E_9725_37FF39DFE160__INCLUDED_)
#define AFX_ARSDOC_H__B1CEA275_F9CB_4E0E_9725_37FF39DFE160__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CARSDoc : public CDocument
{
protected: // create from serialization only
	CARSDoc();
	DECLARE_DYNCREATE(CARSDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CARSDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CARSDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CARSDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARSDOC_H__B1CEA275_F9CB_4E0E_9725_37FF39DFE160__INCLUDED_)
