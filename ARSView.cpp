// ARSView.cpp : implementation of the CARSView class
//
 
#include "stdafx.h"
#include "ARS.h"
#include "PrintResultsDlg.h"
//#include "GetFolderDlg.h"

#include "FilePrepare.h"
#include "SVD.h"
#include "ARSDoc.h"
#include "ARSView.h"
#include "ARSDocument.h"
#include "IndexTermsInDoc.h"
#include "KeyWord.h"
#include "DBManpulation.h"
#include "SVDDel.h"
#include "Query.h"
#include "SearchEngine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//////////////////////////////////////////////////////////////////////////////
//extern CARSDocument		ArabicDocs;
extern CSVD				ARSsvd;
extern CSVDDel			ARSsvd_del;
extern CQuery			ARSquery;
extern CSearchEngine	ARSsearcher;
extern CDBManpulation	ARSdb;


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CARSView

IMPLEMENT_DYNCREATE(CARSView, CFormView)

BEGIN_MESSAGE_MAP(CARSView, CFormView)
	//{{AFX_MSG_MAP(CARSView)
	ON_COMMAND(ID_ADDDOC, OnAdddoc)
	ON_COMMAND(ID_DELDOC, OnDeldoc)
	ON_COMMAND(ID_PRINTDOC, OnPrintdoc)
	ON_CBN_SELCHANGE(IDC_SEARCHLIMIT, OnSelchangeSearchlimit)
	ON_CBN_SELCHANGE(IDC_SIMRATIO, OnSelchangeSimratio)
	ON_EN_CHANGE(IDC_DOCCONTENT, OnChangeDoccontent)
	ON_EN_CHANGE(IDC_EQUERY, OnChangeEquery)
	ON_BN_CLICKED(IDC_SIMDOCS, OnSimdocs)
	ON_BN_CLICKED(IDC_SIMTERMS, OnSimterms)
	ON_BN_CLICKED(IDC_SIMDOCSTERMS, OnSimdocsterms)
	ON_BN_CLICKED(IDC_BSEARCH, OnBsearch)
	ON_EN_ERRSPACE(IDC_EQUERY, OnErrspaceEquery)
	ON_WM_CHAR()
	ON_NOTIFY(TVN_SELCHANGING, IDC_QUERYRESULT, OnSelchangingQueryresult)
	ON_NOTIFY(TVN_SELCHANGED, IDC_QUERYRESULT, OnSelchangedQueryresult)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CARSView construction/destruction

CARSView::CARSView()
	: CFormView(CARSView::IDD)
{
	//{{AFX_DATA_INIT(CARSView)
	m_EQuery = _T("");
	m_SIMDOCS = -1;
	m_SIMTERMS = -1;
	m_SIMDOCSTERMS = -1;
	m_SearchLimit = _T("");
	m_SimRatio = _T("");
	m_DocContent = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CARSView::~CARSView()
{
}

void CARSView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CARSView)
	DDX_Control(pDX, IDC_DOCCONTENT, m_CDocContent);
	DDX_Control(pDX, IDC_SIMRATIO, m_CSimRatio);
	DDX_Control(pDX, IDC_SEARCHLIMIT, m_CSearchLimit);
	DDX_Control(pDX, IDC_QUERYRESULT, m_ResultTree);
	DDX_Control(pDX, IDC_SIMDOCSTERMS, m_CSimDocsTerms);
	DDX_Control(pDX, IDC_SIMTERMS, m_CSimTerms);
	DDX_Control(pDX, IDC_SIMDOCS, m_CSimDocs);
	DDX_Control(pDX, IDC_BSEARCH, m_BSEARCH);
	DDX_Control(pDX, IDC_EQUERY, m_IDC_EQUERY);
	DDX_Text(pDX, IDC_EQUERY, m_EQuery);
	DDV_MaxChars(pDX, m_EQuery, 100);
	DDX_Radio(pDX, IDC_SIMDOCS, m_SIMDOCS);
	DDX_Radio(pDX, IDC_SIMTERMS, m_SIMTERMS);
	DDX_Radio(pDX, IDC_SIMDOCSTERMS, m_SIMDOCSTERMS);
	DDX_CBString(pDX, IDC_SEARCHLIMIT, m_SearchLimit);
	DDV_MaxChars(pDX, m_SearchLimit, 3);
	DDX_CBString(pDX, IDC_SIMRATIO, m_SimRatio);
	DDV_MaxChars(pDX, m_SimRatio, 3);
	DDX_Text(pDX, IDC_DOCCONTENT, m_DocContent);
	//}}AFX_DATA_MAP
}

BOOL CARSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CARSView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	m_CSimDocs.SetCheck(1);
	m_SIMDOCS = 1;
	m_CSearchLimit.SetCurSel(0);
	int n = m_CSearchLimit.GetLBTextLen(m_CSearchLimit.GetCurSel());
    m_CSearchLimit.GetLBText( m_CSearchLimit.GetCurSel(), m_SearchLimit.GetBuffer(n) );
	m_CSimRatio.SetCurSel(0);
	n = m_CSimRatio.GetLBTextLen(m_CSimRatio.GetCurSel());
    m_CSimRatio.GetLBText( m_CSimRatio.GetCurSel(), m_SimRatio.GetBuffer(n) );
	m_BSEARCH.EnableWindow(0);
}

/////////////////////////////////////////////////////////////////////////////
// CARSView diagnostics

#ifdef _DEBUG
void CARSView::AssertValid() const
{
	CFormView::AssertValid();
}

void CARSView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CARSDoc* CARSView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CARSDoc)));
	return (CARSDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CARSView message handlers

void CARSView::OnAdddoc() 
{
	// TODO: Add your command handler code here
	CStringList FilesPathList, FilesNameList;
	FilesPathList.RemoveAll();
	FilesNameList.RemoveAll();
	CFileDialog fdlg(TRUE, "*.txt", NULL, OFN_ALLOWMULTISELECT |OFN_FILEMUSTEXIST
		|OFN_PATHMUSTEXIST |OFN_LONGNAMES , "Text Files (*.txt)|*.txt||", NULL);
	fdlg.m_ofn.lpstrFile = new char[15000];
	fdlg.m_ofn.nMaxFile = 15020;
	//fdlg.m_ofn.lpstrFile[0] = NULL;
	if( fdlg.DoModal() == IDCANCEL )
	{	
		delete []fdlg.m_ofn.lpstrFile;
	}
	else
	{
		for(POSITION stpos = fdlg.GetStartPosition(); stpos!= NULL;)
		{
			FilesPathList.AddTail(fdlg.GetNextPathName( stpos ));
		}
		delete [] fdlg.m_ofn.lpstrFile;
		ARSsvd.DoIndexing(&FilesPathList);
	}

////////////////////////////////////////////////////////
/*	CGetFolderDlg dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}	
*/
///////////////////////////////////////////////////////////
}

void CARSView::OnDeldoc() 
{
	// TODO: Add your command handler code here
	CStringList FilesPathList, FilesNameList;
	CFileDialog fdlg(TRUE, "*.txt", NULL, OFN_ALLOWMULTISELECT |OFN_FILEMUSTEXIST
		|OFN_PATHMUSTEXIST |OFN_LONGNAMES , "Text Files (*.txt)|*.txt||", NULL);
////////////////////////////////////////////////////////////
	FilesPathList.RemoveAll();
	FilesNameList.RemoveAll();
	fdlg.m_ofn.lpstrFile = new char[15000];
	fdlg.m_ofn.nMaxFile = 15020;
	//fdlg.m_ofn.lpstrFile[0] = NULL;
	if( fdlg.DoModal() == IDCANCEL )
	{	
		delete []fdlg.m_ofn.lpstrFile;
	}
	else
	{
		for(POSITION stpos = fdlg.GetStartPosition(); stpos!= NULL;)
		{
			FilesPathList.AddTail(fdlg.GetNextPathName( stpos ));
		}
		delete [] fdlg.m_ofn.lpstrFile;
		ARSsvd_del.FoldOutDoc(FilesPathList);
	}
/////////////////////////////////////////////////////////////
/*	CGetFolderDlg dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}	
*/
////////////////////////////////////////////////////////////////

}

void CARSView::OnPrintdoc() 
{
	// TODO: Add your command handler code here
	CPrintResultsDlg PrnResultsDlg;
	int result = PrnResultsDlg.DoModal();

}

void CARSView::OnSelchangeSearchlimit() 
{
	// TODO: Add your control notification handler code here
	int n = m_CSearchLimit.GetLBTextLen(m_CSearchLimit.GetCurSel());
    m_CSearchLimit.GetLBText( m_CSearchLimit.GetCurSel(), m_SearchLimit.GetBuffer(n) );
}

void CARSView::OnSelchangeSimratio() 
{
	// TODO: Add your control notification handler code here
	int n = m_CSimRatio.GetLBTextLen(m_CSimRatio.GetCurSel());
    m_CSimRatio.GetLBText( m_CSimRatio.GetCurSel(), m_SimRatio.GetBuffer(n) );
}

void CARSView::OnChangeDoccontent() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CFormView::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
}

void CARSView::OnChangeEquery() 
{
	// TODO: Add your control notification handler code here
	m_IDC_EQUERY.GetLine(0,m_EQuery.GetBuffer(m_IDC_EQUERY.LineLength())
		,m_IDC_EQUERY.LineLength());
	if (m_IDC_EQUERY.LineLength())
		m_BSEARCH.EnableWindow(1);
	else
		m_BSEARCH.EnableWindow(0);	
}

void CARSView::OnSimdocs() 
{
	// TODO: Add your control notification handler code here
	m_CSimDocs.SetCheck(1);
	m_SIMDOCS = 1;
	m_CSimTerms.SetCheck(0);
	m_SIMTERMS = 0;
	m_CSimDocsTerms.SetCheck(0);
	m_SIMDOCSTERMS = 0;	
}

void CARSView::OnSimterms() 
{
	// TODO: Add your control notification handler code here
	m_CSimDocs.SetCheck(0);
	m_SIMDOCS = 0;
	m_CSimTerms.SetCheck(1);
	m_SIMTERMS = 1;
	m_CSimDocsTerms.SetCheck(0);
	m_SIMDOCSTERMS = 0;	
	
}

void CARSView::OnSimdocsterms() 
{
	// TODO: Add your control notification handler code here
	m_CSimDocs.SetCheck(0);
	m_SIMDOCS = 0;
	m_CSimTerms.SetCheck(0);
	m_SIMTERMS = 0;
	m_CSimDocsTerms.SetCheck(1);
	m_SIMDOCSTERMS = 1;		
}

void CARSView::OnBsearch() 
{
	RunSearchEngine();
}

void CARSView::RunSearchEngine()
{
	/////////////////////////////////////////////////////////
	// Setting the value of the SearchEngine.SetSimilarity(comboValue)
	//          +
	// Setting the value of the SearchEngine.SetDocTermNum(comboValue)
	//          +    
	// Call to the Query.ProcessQuery(Qvalue, SearchType from checkboxes) 
	/////////////////////////////////////////////////////////
	static BOOL bFirstTime = TRUE;
	char	lpszBuffer[1000];
	
	///////////////////////////////
	HTREEITEM		ahTreeItem[101];
	int				nResult;
	char			Buffer[20];
	///////////////////////////////
	ARSsearcher.SetSimilarity((float)atof(m_SimRatio.GetBuffer(m_SimRatio.GetLength()) ) / 100);
	ARSsearcher.SetSearchLimit(atoi(m_SearchLimit.GetBuffer(m_SearchLimit.GetLength()) ));
	if(m_SIMDOCS)
	{
		bSearchType = 0;
	}
	else
	{
		if(m_SIMTERMS)
			bSearchType = 1;
		else
			bSearchType = 0;//bSearchType = 2;
	}
	if(bFirstTime)
		bFirstTime = FALSE;
	else
		m_ResultTree.DeleteAllItems();

////////////////////////////////normal path of the program ////////////////////////
	m_IDC_EQUERY.GetWindowText(lpszBuffer, m_IDC_EQUERY.GetWindowTextLength()+1);
	ahTreeItem[0] = m_ResultTree.InsertItem(lpszBuffer,
											0, 
											TVI_ROOT);
	m_ResultTree.SetItemData(ahTreeItem[0], 0);
//	CARSDocument TempDoc1;
//	ARSdb.GetDocumentInfoByNumber(459, TempDoc1);

	nResult = ARSquery.ProcessQuery(lpszBuffer, bSearchType);
	if(nResult > ARSsearcher.GetSearchLimit())
		nResult = ARSsearcher.GetSearchLimit();
/////////////////////////////////////////////////////////////////////////
	if(nResult)
	{  
/////////////////////////////////////////////////////////
//		ahTreeItem = new _TREEITEM [nResult + 1];
//		if(!bSearchType)
//			DocInfoList = new CARSDocument [nResult];
//		else
//			TermInfoList = new CKeyWord [nResult];
/////////////////////////////////////////////////////////
		// Initailize the top-level items
	   for (int i = 0; i < nResult; i++)
	   {
		   if(!bSearchType)
		   {
			   ARSdb.GetDocumentInfoByNumber(ARSquery.SimDocList[i].nItem, 
										DocInfoList[i]);
			   if(!DocInfoList[i].m_Ignored)
			   {
				   strcpy(Buffer, DocInfoList[i].m_DocID);
			   }
		   }
		   else
		   {
			   ARSdb.GetTermInfoByNum(ARSquery.SimTermList[i].nItem, Buffer);

		   }
		   ahTreeItem[i+1] = m_ResultTree.InsertItem(Buffer, 
												 ahTreeItem[0],
												 ahTreeItem[i]);
		   m_ResultTree.SetItemData(ahTreeItem[i+1], i+1); 
	   }
//	   delete []ahTreeItem;
//	   if(DocInfoList)
//		   delete []DocInfoList;
//	   else
//		   delete []TermInfoList;
	}
///////////////////////////////end of normal path ///////////////////////////////

/*
///////////////////////////////begin of processing query patch /////////////////
	CStdioFile	constfile("C:\\My Documents\\my corpus\\economic\\Query_Patch.txt", CFile::modeRead|CFile::typeText);
	CStdioFile	QresFile;
	char 		strLine[80];
	int			nQnum;
	while( constfile.ReadString(strLine, 80 ) )
	{
		sscanf(strLine,"%d-%s\r", &nQnum, lpszBuffer);	
		nResult = ARSquery.ProcessQuery(lpszBuffer, bSearchType);
		if(nResult > ARSsearcher.GetSearchLimit())
			nResult = ARSsearcher.GetSearchLimit();
		/////////////////////////////////////////////////////////////
		if(nResult)
		{  
			sprintf(strLine,"C:\\My Documents\\my corpus\\economic\\QT%d.txt",nQnum);
			QresFile.Open( strLine, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
			// Iterate through items resulted
			for (int i = 0; i < nResult; i++)
			{
				if(!bSearchType)
				{
					ARSdb.GetDocumentInfoByNumber(ARSquery.SimDocList[i].nItem, 
						DocInfoList[i]);
					if(!DocInfoList[i].m_Ignored)
					{
						sprintf(strLine,"%s\n",DocInfoList[i].m_DocID);
						QresFile.WriteString(strLine);
					}
				}
				else
				{
					ARSdb.GetTermInfoByNum(ARSquery.SimTermList[i].nItem, Buffer);
					sprintf(strLine,"%s\n", Buffer);
					QresFile.WriteString(strLine);
				}
			}
			QresFile.Close();
		}		
	}
	constfile.Close();
//////////////////////end of processing query patch //////////////////////////////
*/
}

void CARSView::OnErrspaceEquery() 
{
	// TODO: Add your control notification handler code here
	AfxMessageBox("ÇáÃÓÊÝÓÇÑ ÃØæá ãä ÍÌã ÇáãÊÇÍ");
	
}


void CARSView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CFormView::OnChar(nChar, nRepCnt, nFlags);
}

void CARSView::OnSelchangingQueryresult(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

void CARSView::OnSelchangedQueryresult(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CFilePrepare	fpDocs;
	unsigned long   Index;
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
//	AfxMessageBox("changed");
	if(!bSearchType)
	{
		Index = m_ResultTree.GetItemData(m_ResultTree.GetSelectedItem());
		if(Index)
		{
			fpDocs.OpenFile(DocInfoList[Index-1].m_Location);
			m_CDocContent.SetWindowText(fpDocs.pFileContent);
		}
		else
			m_CDocContent.SetWindowText(" ");
	}
	else
	{
		m_CDocContent.SetWindowText(" ");
	}
	*pResult = 0;
}
