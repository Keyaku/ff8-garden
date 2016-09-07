// ChildFrm.h : interface of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDFRM_H__AC2ACF29_C1E3_11D3_815D_AF6BF6E47A3B__INCLUDED_)
#define AFX_CHILDFRM_H__AC2ACF29_C1E3_11D3_815D_AF6BF6E47A3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "ChildView.h"

class CChildFrame : public CMDIChildWnd
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnClose();
	virtual void OnSize(UINT nType, int cx, int cy);
	//}}AFX_VIRTUAL

// Implementation
public:
	CFile file;
	virtual void LoadFile (CString strFile);
	// view for the client area of the frame.
//	CChildView m_wndView;
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrame)
	afx_msg void OnFileClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__AC2ACF29_C1E3_11D3_815D_AF6BF6E47A3B__INCLUDED_)
