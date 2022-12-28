// ARSDoc.cpp : implementation of the CARSDoc class
//

#include "stdafx.h"
#include "ARS.h"

#include "ARSDoc.h"
#include "ARSView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CARSView			*pARSView;
/////////////////////////////////////////////////////////////////////////////
// CARSDoc

IMPLEMENT_DYNCREATE(CARSDoc, CDocument)

BEGIN_MESSAGE_MAP(CARSDoc, CDocument)
	//{{AFX_MSG_MAP(CARSDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CARSDoc construction/destruction

CARSDoc::CARSDoc()  
{
	// TODO: add one-time construction code here

}

CARSDoc::~CARSDoc()
{
}

BOOL CARSDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	for (POSITION Pos = GetFirstViewPosition();Pos!= NULL;)
	{
		 pARSView = (CARSView*)GetNextView(Pos);
	}

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CARSDoc serialization

void CARSDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CARSDoc diagnostics

#ifdef _DEBUG
void CARSDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CARSDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CARSDoc commands
