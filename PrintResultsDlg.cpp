// PrintResultsDlg.cpp : implementation file
//
 
#include "stdafx.h"
#include "ARS.h"
#include "PrintResultsDlg.h"
#include "ARSView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CARSView			*pARSView;
/////////////////////////////////////////////////////////////////////////////
// CPrintResultsDlg dialog


CPrintResultsDlg::CPrintResultsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrintResultsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrintResultsDlg)
	m_PrnDocsResultsVal = -1;
	m_PrnDocumentsVal = -1;
	m_PrnResultsVal = -1;
	//}}AFX_DATA_INIT
}


void CPrintResultsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrintResultsDlg)
	DDX_Control(pDX, IDC_PRNRESULTS, m_CPrnResults);
	DDX_Control(pDX, IDC_PRNDOCUMENTS, m_CPrnDocuments);
	DDX_Control(pDX, IDC_PRNDOCSRESULTS, m_CPrnDocsResults);
	DDX_Control(pDX, IDC_FILELIST, m_CFileList);
	DDX_Control(pDX, IDC_EPRNQUERY, m_CePrnQuery);
	DDX_Radio(pDX, IDC_PRNDOCSRESULTS, m_PrnDocsResultsVal);
	DDX_Radio(pDX, IDC_PRNDOCUMENTS, m_PrnDocumentsVal);
	DDX_Radio(pDX, IDC_PRNRESULTS, m_PrnResultsVal);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrintResultsDlg, CDialog)
	//{{AFX_MSG_MAP(CPrintResultsDlg)
	ON_BN_CLICKED(IDC_PRNRESULTS, OnPrnresults)
	ON_BN_CLICKED(IDC_PRNDOCUMENTS, OnPrndocuments)
	ON_BN_CLICKED(IDC_PRNDOCSRESULTS, OnPrndocsresults)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrintResultsDlg message handlers

void CPrintResultsDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CPrintResultsDlg::OnPrnresults() 
{
	// TODO: Add your control notification handler code here
	m_CPrnResults.SetCheck(1);
	m_PrnResultsVal = 1;
	m_CPrnDocuments.SetCheck(0);
	m_PrnDocumentsVal = 0;
	m_CPrnDocsResults.SetCheck(0);
	m_PrnDocsResultsVal = 0;

	
}

void CPrintResultsDlg::OnPrndocuments() 
{
	// TODO: Add your control notification handler code here
	m_CPrnResults.SetCheck(0);
	m_PrnResultsVal = 0;
	m_CPrnDocuments.SetCheck(1);
	m_PrnDocumentsVal = 1;
	m_CPrnDocsResults.SetCheck(0);
	m_PrnDocsResultsVal = 0;
	
}

void CPrintResultsDlg::OnPrndocsresults() 
{
	// TODO: Add your control notification handler code here
	m_CPrnResults.SetCheck(0);
	m_PrnResultsVal = 0;
	m_CPrnDocuments.SetCheck(0);
	m_PrnDocumentsVal = 0;
	m_CPrnDocsResults.SetCheck(1);
	m_PrnDocsResultsVal = 1;
	
}

BOOL CPrintResultsDlg::OnInitDialog() 
{
	char	Buffer[1000];
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//m_CePrnQuery.SetWindowText("hello ya mickkkkkkkkkkkkyy");
	m_CPrnResults.SetCheck(1);
	m_PrnResultsVal = 1;
	pARSView->m_IDC_EQUERY.GetWindowText(Buffer, pARSView->m_IDC_EQUERY.GetWindowTextLength()+1 );
	m_CePrnQuery.SetWindowText(Buffer);
	HTREEITEM hParentItem = pARSView->m_ResultTree.GetNextItem(NULL, TVGN_CHILD);
//////////////////////////////////////////////////
   HTREEITEM hNextItem;
   HTREEITEM hChildItem = pARSView->m_ResultTree.GetChildItem(hParentItem);

   while (hChildItem != NULL)
   {
      hNextItem = pARSView->m_ResultTree.GetNextItem(hChildItem, TVGN_NEXT);
	  m_CFileList.AddString(pARSView->m_ResultTree.GetItemText(hChildItem));
      hChildItem = hNextItem;
   }
//////////////////////////////////////////////////

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
