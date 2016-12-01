// Garden.h : main header file for the GARDEN application
//

#if !defined(AFX_GARDEN_H__AC2ACF23_C1E3_11D3_815D_AF6BF6E47A3B__INCLUDED_)
#define AFX_GARDEN_H__AC2ACF23_C1E3_11D3_815D_AF6BF6E47A3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'ui_win32/StdAfx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGardenApp:
// See Garden.cpp for the implementation of this class
//

class CGardenApp : public CWinApp
{
public:
	CGardenApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGardenApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	HMENU m_hMDIMenu;
	HACCEL m_hMDIAccel;

public:
	CString strProjectPath;
	CString strProjectFile;
	//{{AFX_MSG(CGardenApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileNew();
	afx_msg void OnDecompile();
	afx_msg void OnOpenproject();
	afx_msg void OnCompile();
	afx_msg void OnOpenfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GARDEN_H__AC2ACF23_C1E3_11D3_815D_AF6BF6E47A3B__INCLUDED_)
