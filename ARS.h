// ARS.h : main header file for the ARS application
// 

#if !defined(AFX_ARS_H__AD6115A9_F7F2_49DE_B067_D71756210EBE__INCLUDED_)
#define AFX_ARS_H__AD6115A9_F7F2_49DE_B067_D71756210EBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "math.h"

/////////////////////////////////////////////////////////////////////////////
// CARSApp:
// See ARS.cpp for the implementation of this class
//

class CARSApp : public CWinApp
{
public:
	CARSApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CARSApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CARSApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ARS_H__AD6115A9_F7F2_49DE_B067_D71756210EBE__INCLUDED_)
