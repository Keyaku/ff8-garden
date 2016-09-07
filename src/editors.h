// editors.h: interface for the CEditorText class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EDITORS_H__F15177C1_C3C8_11D3_815D_A74CDEBE033B__INCLUDED_)
#define AFX_EDITORS_H__F15177C1_C3C8_11D3_815D_A74CDEBE033B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChildFrm.h"


/////////////////////////////////////////////////////////////////////////////
// CFF8Text window

class CFF8Text : public CWnd
{
// Construction
public:
	CFF8Text();

// Attributes
public:

// Operations
public:

// Overrides
	virtual BOOL Create(const RECT& rect, CWnd* pParentWnd, UINT nID);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFF8Text)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	static LPCTSTR GetLocationName (int code);
	static LPCTSTR GetCharName (int code);
	void InsertString (LPCTSTR str);
	CString text;
	CImageList *il;
	void SetText (LPCTSTR src);
	HBRUSH bgbrush;
	virtual ~CFF8Text();

	void OnSetFocus(CWnd* pOldWnd);
	void OnKillFocus(CWnd* pNewWnd);

	// Generated message map functions
protected:
	void CalcHeight();
	void MoveCursor (int pos);
	POINT caretpos;
	int topoffset;
	int height;
	int curpos;
//	BYTE text[0x2000];
	//{{AFX_MSG(CFF8Text)
	afx_msg void OnPaint();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////




class CFF8Edit : public CListBox
{
// Construction
public:
	CFF8Edit();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFF8Edit)
	//}}AFX_VIRTUAL

// Implementation
public:
	HBRUSH bgbrush;
	CString *src;
	int SetText (CString *src, int lines);
	int *height;
	UINT nLines;
	CImageList *il;
	virtual ~CFF8Edit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CFF8Edit)
	afx_msg void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};



class CEditorText : public CChildFrame  
{
	DECLARE_DYNCREATE(CEditorText)
public:

	CImageList il;
	int nLines;
	void LoadFile (CString strFile);
	void OnSize (UINT nType, int cx, int cy);
	CFF8Text edit;
	CFF8Edit text;
	CEditorText();
	virtual ~CEditorText();


protected:
	CMenu mnuDrop;
	void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	CToolBarCtrl toolbar;
	BOOL PreCreateWindow(CREATESTRUCT& cs);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);

	CString *buf;
	
	void OnSelChange();

	DECLARE_MESSAGE_MAP()

};


class CEditorTexture : public CChildFrame  
{
	DECLARE_DYNCREATE(CEditorTexture)
public:
	void LoadFile (CString strFile);
	CEditorTexture();
	virtual ~CEditorTexture();

protected:
	CBitmap bmpAlpha;
	void OnSize (UINT nType, int cx, int cy);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	CStatic m_Canvas;
	CStatic m_Border;
	CBitmap bmpTexture;
	int type;		// Type of texture
					// 0: TEX
					// 1: LZS (screen)
					// 2: TIM
					// 3:

	int iWidth;
	int iHeight;
	int iColors;

};

#endif // !defined(AFX_EDITORS_H__F15177C1_C3C8_11D3_815D_A74CDEBE033B__INCLUDED_)
