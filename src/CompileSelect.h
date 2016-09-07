#if !defined(AFX_COMPILESELECT_H__FFFFEEA1_C76A_11D3_815D_0020183A5DA9__INCLUDED_)
#define AFX_COMPILESELECT_H__FFFFEEA1_C76A_11D3_815D_0020183A5DA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CompileSelect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCompileSelect dialog

class CCompileSelect : public CDialog
{
// Construction
public:
	CCompileSelect(CWnd* pParent = NULL);   // standard constructor

	BOOL *fFlags;

// Dialog Data
	//{{AFX_DATA(CCompileSelect)
	enum { IDD = IDD_COMPILE };
	CCheckListBox	m_Main;
	CCheckListBox	m_Field;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompileSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCompileSelect)
	virtual BOOL OnInitDialog();
	afx_msg void OnCompile();
	afx_msg void OnCompileAll();
	afx_msg void OnCompileSelected();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPILESELECT_H__FFFFEEA1_C76A_11D3_815D_0020183A5DA9__INCLUDED_)
