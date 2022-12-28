// ARS.cpp : Defines the class behaviors for the application.
// 

#include "stdafx.h"
#include "ARS.h"

#include "MainFrm.h"
#include "ARSDoc.h"
#include "ARSView.h"
///////////////////////////// include files of the ARS app. ////
#include "ARSDocument.h"
#include "KeyWord.h"
#include "IndexTermsInDoc.h"
#include "DBManpulation.h"
#include "CommonWord.h"
#include "Indexer.h"
#include "SVD.h"
#include "SVDDel.h"
#include "Query.h"
#include "SearchEngine.h"
////////////////////////////////////////////////////////////////
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CARSApp

BEGIN_MESSAGE_MAP(CARSApp, CWinApp)
	//{{AFX_MSG_MAP(CARSApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CARSApp construction

CARSApp::CARSApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CARSApp object

CARSApp theApp;
/////////////////////////////////////////////////////////////////////////////
///////////////////////////////// Application Def. classes ////////////////
/**/#define MAX_FACTORS_K 300 // it is the more suitable number...
// NOW IS MORE CONCEPTUAL ....
CDBManpulation		ARSdb;
CCommonWord			ArabicCommonWord;
CARSDocument		ArabicDocs;
CIndexer			ARSIndexer;
CKeyWord			ARSKWords;
CIndexTermsInDoc	ARSITerms;
CSVD				ARSsvd(MAX_FACTORS_K);
CSVDDel				ARSsvd_del;
CQuery				ARSquery;
CSearchEngine		ARSsearcher;
CARSView			*pARSView;
/////////////////////////////////////////////////////////////////////////////
// CARSApp initialization

BOOL CARSApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CARSDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CARSView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->SetWindowText("äÙÇã ÇÓÊÑÌÇÚ ÇáæËÇÆÞ ÈÇááÛÉ ÇáÚÑÈíÉ ARS");
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();
	/////////////////////////////////////////////
	// Activate the Arabic keyboard layout
	//WORD xy = MAKELANGID(LANG_ARABIC, SUBLANG_ARABIC_EGYPT);
	HKL hklArabicEgypt = LoadKeyboardLayout("0x0c01", 
		                 KLF_SETFORPROCESS|KLF_ACTIVATE|KLF_SUBSTITUTE_OK|KLF_SETFORPROCESS);
	ActivateKeyboardLayout(hklArabicEgypt, KLF_SETFORPROCESS|KLF_REORDER);

	/////////////////////////////////////////////
	if( ARSdb.OpenConnection() )
	{
		AfxMessageBox("NO CONNECTION WAS ESTABLISHED");
		::exit(1);
	}
	if( !ARSdb.LoadCommonWords() )
	{
		AfxMessageBox("NO Load of commonWords");
		::exit(1);
	}	
/////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////
	if(ARSdb.CheckDocBase()) // the doc-base has docs and already indexed
/**/	{
		ARSsvd.GetS();
		ARSsvd.GetV();
		ARSsvd.GetU();	
		ARSquery.DoScaleofTerms();
		if( !ARSdb.GetDocTermInfo() )
		{
			AfxMessageBox("Couldn't access the ARSdb");
			::exit(1);
		}
	////////////////////////////////////////////////////////////////////////////////
		ARSquery.SimDocList = new ItemList[ARSdb.MaxDoc+1];
		if(ARSquery.SimDocList)
		{
			ARSquery.SimTermList = new ItemList[ARSdb.MaxTerm+1];
			if(ARSquery.SimTermList == NULL)
				AfxMessageBox("Error In Allocation of Term and Doc Lists-->Query");
		}
		else
		{
			AfxMessageBox("Error In Allocation of Term and Doc Lists-->Query");
		}
	}

/////////////////////////////////////trials for the db-layer ////////////
//	BOOL x = ArabicCommonWord.IsWordCommon("Çä");
//	CARSDocument	Docs;
//	ARSdb.GetDocumentInfoByName("c:\\cc\\DocInfo.txt", Docs);
//	ARSdb.GetDocumentInfoByNumber(459, Docs);
//	ARSdb.GetDocumentInfoByNumber(450, Docs);
//	CKeyWord		kw;
//	kw.m_Gfi = 1234567890;
//	kw.m_GlobalWeight = -2.624663;
//	strcpy(kw.m_TermValue, "xyz");
//	ARSdb.AddNewTerm(kw);
//	LONG xx;
//	ARSdb.GetTermInfoByName("xyz1", xx);
//	CIndexTermsInDoc TermDocInfo;
//	TermDocInfo.SetIndexTermInfo(1,1,2.5,40);
//	ARSdb.AddIndexTerm(TermDocInfo);
//	ARSdb.UpdateDoc(1, 6064);
//	LONG MinDoc, MaxDoc, MaxTerm;
//	ARSdb.GetDocTermInfo(MinDoc,MaxDoc, MaxTerm);
//	mwArray TMmat;
//	ARSdb.FillArray(TMmat);
//	ArabicDocs.CountFreq("C:\\My Documents\\my corpus\\economic\\e1.txt");
/////////////////////////////////////////////////////////////////////////
	//BOOL xx = ARSIndexer.CheckDocTermBase();
	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CARSApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CARSApp message handlers

