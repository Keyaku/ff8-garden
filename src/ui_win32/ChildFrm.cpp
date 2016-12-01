// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "ui_win32/StdAfx.h"
#include "Garden.h"

#include "ui_win32/ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
		ON_COMMAND(ID_FILE_CLOSE, OnFileClose)
		ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildFrame construction/destruction

CChildFrame::CChildFrame()
{
	// TODO: add member initialization code here
	
}

CChildFrame::~CChildFrame()
{

}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CMDIChildWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0,LoadCursor(NULL,IDC_ARROW),(HBRUSH)GetStockObject(LTGRAY_BRUSH));

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChildFrame message handlers
void CChildFrame::OnFileClose() 
{
	// To close the frame, just send a WM_CLOSE, which is the equivalent
	// choosing close from the system menu.

	SendMessage(WM_CLOSE);
}

int CChildFrame::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// create a view to occupy the client area of the frame
//	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, 
//		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
//	{
//		TRACE0("Failed to create view window\n");
//		return -1;
//	}

	return 0;
}

BOOL CChildFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	// let the view have first crack at the command
//	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
//		return TRUE;
	
	// otherwise, do default handling
	return CMDIChildWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}






void CChildFrame::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if ((HFILE)file != (HFILE)-1)
		file.Close();

	CMDIChildWnd::OnClose();
}

void CChildFrame::OnSize(UINT nType, int cx, int cy) 
{
	CMDIChildWnd::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

void CChildFrame::LoadFile(CString strFile)
{
	file.Open(strFile,CFile::modeReadWrite);

}
