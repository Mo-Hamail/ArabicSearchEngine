// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently 
//

#if !defined(AFX_STDAFX_H__3CD3D477_DDC8_4677_8465_2F569F24E42F__INCLUDED_)
#define AFX_STDAFX_H__3CD3D477_DDC8_4677_8465_2F569F24E42F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls

//////////////////////////////////////////// ADO PREPARATION //////////
#import  <C:\\Windows\\WinSxS\\wow64_microsoft-windows-m..ents-mdac-ado15-dll_31bf3856ad364e35_10.0.17134.829_none_f84989f5fb064d27\\msado15.dll> rename("EOF", "adoEOF")
//#import  <C:\\WINNT\\system32\\dllcache\\msado15.dll> rename("EOF", "adoEOF")
#include <icrsint.h> //Include the following file in your application in order to 
					 // use the Visual C++ Extensions for ADO
#include <comdef.h>
//////////////////////////////////////////////////////////////////////
//////////////////////////////////// Matlab	PREPARARATION /////////////
#include "matlab.hpp"
///////////////////////////////////////////////////////////////////////
//////////////////////////////////// BASE Class //////////////////////
#include "ir.h"
//////////////////////////////////////////////////////////////////////
#endif // _AFX_NO_AFXCMN_SUPPORT


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__3CD3D477_DDC8_4677_8465_2F569F24E42F__INCLUDED_)

