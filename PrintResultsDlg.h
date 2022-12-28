#if !defined(AFX_PRINTRESULTSDLG_H__D9931E3F_EF4B_40B9_8899_661EA14CE6DB__INCLUDED_)
#define AFX_PRINTRESULTSDLG_H__D9931E3F_EF4B_40B9_8899_661EA14CE6DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrintResultsDlg.h : header file
//
 
/////////////////////////////////////////////////////////////////////////////
// CPrintResultsDlg dialog

class CPrintResultsDlg : public CDialog
{
// Construction
public:
	CPrintResultsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPrintResultsDlg)
	enum { IDD = IDD_PRINTDIALOG };
	CButton	m_CPrnResults;
	CButton	m_CPrnDocuments;
	CButton	m_CPrnDocsResults;
	CListBox	m_CFileList;
	CEdit	m_CePrnQuery;
	int		m_PrnDocsResultsVal;
	int		m_PrnDocumentsVal;
	int		m_PrnResultsVal;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintResultsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrintResultsDlg)
	virtual void OnOK();
	afx_msg void OnPrnresults();
	afx_msg void OnPrndocuments();
	afx_msg void OnPrndocsresults();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTRESULTSDLG_H__D9931E3F_EF4B_40B9_8899_661EA14CE6DB__INCLUDED_)
