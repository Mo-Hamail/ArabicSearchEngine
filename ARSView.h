// ARSView.h : interface of the CARSView class
// 
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARSVIEW_H__6C018A70_82FD_4DDC_A1AF_4C4813898B9E__INCLUDED_)
#define AFX_ARSVIEW_H__6C018A70_82FD_4DDC_A1AF_4C4813898B9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ARSDocument.h"
#include "KeyWord.h"
#include "ARSDoc.h"
class CARSView : public CFormView
{
protected: // create from serialization only
	CARSView();
	DECLARE_DYNCREATE(CARSView)

public:
	//{{AFX_DATA(CARSView)
	enum { IDD = IDD_ARS_FORM };
	CEdit	m_CDocContent;
	CComboBox	m_CSimRatio;
	CComboBox	m_CSearchLimit;
	CTreeCtrl	m_ResultTree;
	CButton	m_CSimDocsTerms;
	CButton	m_CSimTerms;
	CButton	m_CSimDocs;
	CButton	m_BSEARCH;
	CEdit	m_IDC_EQUERY;
	CString	m_EQuery;
	int		m_SIMDOCS;
	int		m_SIMTERMS;
	int		m_SIMDOCSTERMS;
	CString	m_SearchLimit;
	CString	m_SimRatio;
	CString	m_DocContent;
	//}}AFX_DATA

// Attributes
	CARSDocument	DocInfoList[101];
	CKeyWord		TermInfoList[101];
	BOOL			bSearchType;
public:
	CARSDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CARSView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CARSView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	void RunSearchEngine();
	//{{AFX_MSG(CARSView)
	afx_msg void OnAdddoc();
	afx_msg void OnDeldoc();
	afx_msg void OnPrintdoc();
	afx_msg void OnSelchangeSearchlimit();
	afx_msg void OnSelchangeSimratio();
	afx_msg void OnChangeDoccontent();
	afx_msg void OnChangeEquery();
	afx_msg void OnSimdocs();
	afx_msg void OnSimterms();
	afx_msg void OnSimdocsterms();
	afx_msg void OnBsearch();
	afx_msg void OnErrspaceEquery();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSelchangingQueryresult(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedQueryresult(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in ARSView.cpp
inline CARSDoc* CARSView::GetDocument()
   { return (CARSDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARSVIEW_H__6C018A70_82FD_4DDC_A1AF_4C4813898B9E__INCLUDED_)
