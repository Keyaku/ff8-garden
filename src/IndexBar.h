#if !defined(AFX_INDEXBAR_H__F84EFBE1_9B93_11D3_815D_BF44DB5ED574__INCLUDED_)
#define AFX_INDEXBAR_H__F84EFBE1_9B93_11D3_815D_BF44DB5ED574__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IndexBar.h : header file
//

//#include "lgp.h"

/////////////////////////////////////////////////////////////////////////////
// CIndexBar frame

class CIndexBar : public CWnd
{
	DECLARE_DYNCREATE(CIndexBar)
protected:

// Attributes
public:

// Operations
public:
	void Update();
	CTreeCtrl * GetDirBox();
	int sortby;
	bool bRevOrder;

	void Sort ();
	CListCtrl * GetList();
	CIndexBar();           // protected constructor used by dynamic creation
	virtual ~CIndexBar();           // protected constructor used by dynamic creation

	BOOL Create(CWnd* pParentWnd);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIndexBar)
	public:
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:
	CImageList il;
	CListCtrl list;
	CTreeCtrl dirbox;

	int width;
	CFont fntTitle;
//	virtual ~CIndexBar();

	// Generated message map functions
	//{{AFX_MSG(CIndexBar)
	afx_msg LRESULT OnSizeParent(WPARAM, LPARAM);
	afx_msg void OnPaint();
	afx_msg void OnClickDir(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickIndex(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickHeader(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRClickIndex(NMHDR* pNMHDR, LRESULT* pResult); 
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDrawItem(UINT nIDCtrl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INDEXBAR_H__F84EFBE1_9B93_11D3_815D_BF44DB5ED574__INCLUDED_)
