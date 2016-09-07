// IndexBar.cpp : implementation file
//

#include "stdafx.h"
//#include "Gast.h"
#include "Garden.h"
#include "IndexBar.h"
#include "resource.h"
#include <afxpriv.h>
#include "project.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


extern CProject theProject;


/////////////////////////////////////////////////////////////////////////////
// CIndexBar

IMPLEMENT_DYNCREATE(CIndexBar, CWnd)

CIndexBar::CIndexBar()
{
	fntTitle.CreateFont(-12,0,0,0,0,0,0,0,0,0,0,0,0,"Tahoma");
	if (!(HFONT)fntTitle)
		fntTitle.CreateFont(-12,0,0,0,0,0,0,0,0,0,0,0,0,"Arial");
	if (!(HFONT)fntTitle)
		fntTitle.FromHandle((HFONT)GetStockObject(ANSI_VAR_FONT));

	width = 205;
	sortby = 0;
	bRevOrder = 0;
}

CIndexBar::~CIndexBar()
{
	fntTitle.DeleteObject();

}


BEGIN_MESSAGE_MAP(CIndexBar, CWnd)
	//{{AFX_MSG_MAP(CIndexBar)
	ON_MESSAGE(WM_SIZEPARENT, OnSizeParent)
	ON_WM_PAINT()
	ON_NOTIFY(TVN_SELCHANGED, ID_INDEX_DIR, OnClickDir)
	ON_NOTIFY(NM_DBLCLK, ID_INDEX_CTRL, OnClickIndex)
	ON_NOTIFY(HDN_ITEMCLICK, 0, OnClickHeader)
	ON_NOTIFY(NM_RCLICK, ID_INDEX_CTRL, OnRClickIndex)
	ON_WM_SIZE()
	ON_MESSAGE(WM_DRAWITEM, OnDrawItem)
	ON_NOTIFY(NM_RETURN, ID_INDEX_CTRL, OnClickIndex)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIndexBar message handlers


afx_msg LRESULT CIndexBar::OnSizeParent(WPARAM wParam, LPARAM lParam)
{
	AFX_SIZEPARENTPARAMS *params = (AFX_SIZEPARENTPARAMS*)lParam;
	
	SetWindowPos(NULL,params->rect.left,params->rect.top,width,params->rect.bottom - params->rect.top,SWP_NOZORDER);

	params->rect.left += width;
	//params->rect.right -= 202;
	params->sizeTotal.cx -= width;

	return 0;
}

void CIndexBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CDC *wdc = GetWindowDC();
	
	// TODO: Add your message handler code here
	COLORREF dark, light, face;
	CRect rc;
	GetClientRect((LPRECT)rc);
	dark = GetSysColor(COLOR_BTNSHADOW);
	light = GetSysColor(COLOR_BTNHILIGHT);
	face = GetSysColor(COLOR_BTNFACE);

	dc.SelectObject(&fntTitle);
	dc.SetBkMode(TRANSPARENT);

	dc.Draw3dRect(5,6,3,19,light,dark);
	dc.Draw3dRect(9,6,3,19,light,dark);

	dc.TextOut(17,8,"Project files");

//	wdc->FillSolidRect(0,2,5,rc.Height()-4,face);
//	wdc->FillSolidRect(rc.Width()-10,2,6,rc.Height()-4,face);
	wdc->Draw3dRect(0,0,width-5,2,dark,light);
	wdc->Draw3dRect(0,rc.Height()-2,width-5,2,dark,light);
	wdc->Draw3dRect(width-6,0,2,rc.Height(),dark,light);

	// Do not call CDialogBar::OnPaint() for painting messages
}


void CIndexBar::OnClickIndex(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// If an item has been double-clicked, open it
	if (list.GetSelectedCount() != 0) {
		extern CGardenApp theApp;
		theApp.OnOpenfile();
//		::SendMessage((HWND)AfxGetMainWnd(),WM_COMMAND,ID_OPENFILE,0);
	}

	*pResult = 0;
}

void CIndexBar::OnClickHeader(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *hd = (HD_NOTIFY*)pNMHDR;

	switch (hd->iItem) {
	case 0:	if (sortby == 1) bRevOrder = !bRevOrder;
		else bRevOrder = false;
		sortby = 1; break;
	case 1: if (sortby == 3) bRevOrder = !bRevOrder;
		else bRevOrder = false;
		sortby = 3; break;
	default: break;
	}

	Sort();

	*pResult = 0;
}

void CIndexBar::OnRClickIndex(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CMenu menu, *mnu;
	menu.LoadMenu(IDR_INDEX);

	// If an item has been right-clicked, show item context menu
	if (list.GetSelectedCount() != 0) {
		mnu = menu.GetSubMenu(0);
		mnu->SetDefaultItem(0,true);
		
		POINT pnt;
		list.GetItemPosition(list.GetSelectionMark(),&pnt);
		list.ClientToScreen(&pnt);
		
		mnu->TrackPopupMenu(TPM_RIGHTBUTTON,pnt.x+14,pnt.y+14,GetParent());
		
	}
	// If not, show list context menu
	else {
		mnu = menu.GetSubMenu(1);
		mnu->GetSubMenu(0)->CheckMenuRadioItem(0,3,sortby,MF_BYPOSITION);
		mnu->GetSubMenu(0)->CheckMenuItem(ID_ARCHIVE_SORTREV, MF_BYCOMMAND | ( bRevOrder ? MF_CHECKED : MF_UNCHECKED ));
				
		POINT pnt;
		GetCursorPos(&pnt);
		mnu->TrackPopupMenu(TPM_RIGHTBUTTON,pnt.x,pnt.y,GetParent());

	}

	menu.DestroyMenu();

	*pResult = 0;
}

void CIndexBar::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	if (!m_hWnd) return;
	
	if (!list.m_hWnd) return;
	
	CRect rc;
	GetClientRect((LPRECT)rc);
	
/*	LOGFONT logfnt;
	::GetObject(GetStockObject(ANSI_VAR_FONT),sizeof(LOGFONT),&logfnt);
	titleheight = logfnt.lfHeight < 0 ? -logfnt.lfHeight : logfnt.lfHeight;
*/

	dirbox.SetWindowPos(NULL,5,17+12,rc.Width()-18,103,SWP_NOZORDER);
	list.SetWindowPos(NULL,5,17+122,rc.Width()-18,rc.Height()-27-122,SWP_NOZORDER);


	// TODO: Add your message handler code here
	
}

BOOL CIndexBar::Create(CWnd* pParentWnd)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = AfxGetAfxWndProc();
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = AfxGetInstanceHandle();
	wcex.hIcon = NULL;
	wcex.hCursor = LoadCursor(NULL,IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = "GastIndexBar32";
	wcex.hIconSm = NULL;

	RegisterClassEx(&wcex);
	
	BOOL r = CWnd::Create("GastIndexBar32","GastIndexBar",WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN,CRect(0,0,100,100),pParentWnd,ID_INDEX_BAR);

	if (!r) return false;

	CBitmap bmp;
	bmp.LoadBitmap(IDB_TYPES);

	il.Create(14,14,ILC_COLOR | ILC_MASK,0,32);
	il.Add(&bmp,RGB(255,0,255));

	bmp.DeleteObject();

	dirbox.Create(WS_CHILDWINDOW | WS_VISIBLE | TVS_FULLROWSELECT | TVS_SINGLEEXPAND | TVS_SHOWSELALWAYS, CRect(0,0,100,100),this,ID_INDEX_DIR);
	dirbox.ModifyStyleEx(0,WS_EX_CLIENTEDGE);
	//dirbox.Create(WS_CHILDWINDOW | WS_VISIBLE | CBS_DROPDOWNLIST,CRect(0,0,100,100),this,ID_INDEX_DIR);
	dirbox.SetImageList(&il,TVSIL_NORMAL);
	dirbox.SetIndent(0);
	
	list.Create(WS_VISIBLE | WS_DISABLED | WS_CHILDWINDOW | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SHAREIMAGELISTS, CRect(0,0,100,100), this, ID_INDEX_CTRL);

	list.ModifyStyleEx(0,WS_EX_CLIENTEDGE);
//	list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	list.SetImageList(&il,LVSIL_SMALL);

	list.InsertColumn(0,"Name",LVCFMT_LEFT,106,0);
//	list.InsertColumn(1,"Type",LVCFMT_CENTER,40,1);
	list.InsertColumn(1,"Size",LVCFMT_RIGHT,width-128-GetSystemMetrics(SM_CXHSCROLL),1);


	return r;

}


BOOL CIndexBar::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	BOOL r = CWnd::DestroyWindow();

	UnregisterClass("GastIndexBar32",AfxGetInstanceHandle());

	return r;

}


CListCtrl * CIndexBar::GetList()
{
	if (!list.m_hWnd) return NULL;
	return &list;
}



/*
// Sort function
int CALLBACK sort_none		(LPARAM a, LPARAM b, LPARAM p) {
	return a-b; }
int CALLBACK sort_none_r	(LPARAM a, LPARAM b, LPARAM p) {
	return b-a; }
int CALLBACK sort_name		(LPARAM a, LPARAM b, LPARAM p) {
	return strcmpi(((CLGP*)p)->GetSlotName((USHORT)a),((CLGP*)p)->GetSlotName((USHORT)b)); }
int CALLBACK sort_name_r	(LPARAM a, LPARAM b, LPARAM p) {
	return strcmpi(((CLGP*)p)->GetSlotName((USHORT)b),((CLGP*)p)->GetSlotName((USHORT)a)); }
int CALLBACK sort_type		(LPARAM a, LPARAM b, LPARAM p) {
	return strcmpi(((CLGP*)p)->GetSlotSuffix((USHORT)a),((CLGP*)p)->GetSlotSuffix((USHORT)b)); }
int CALLBACK sort_type_r	(LPARAM a, LPARAM b, LPARAM p) {
	return strcmpi(((CLGP*)p)->GetSlotSuffix((USHORT)b),((CLGP*)p)->GetSlotSuffix((USHORT)a)); }
int CALLBACK sort_size		(LPARAM a, LPARAM b, LPARAM p) {
	return ((CLGP*)p)->GetSlotSize((USHORT)a)-((CLGP*)p)->GetSlotSize((USHORT)b); }
int CALLBACK sort_size_r	(LPARAM a, LPARAM b, LPARAM p) {
	return ((CLGP*)p)->GetSlotSize((USHORT)b)-((CLGP*)p)->GetSlotSize((USHORT)a); }
*/
void CIndexBar::Sort()
{
	BOOL rev = bRevOrder;

/*	extern CLGP theLGP;

	switch (sortby) {
	case 0: if (rev) list.SortItems(sort_none_r, (LONG)&theLGP);
		else list.SortItems(sort_none, (LONG)&theLGP);
		break;
	case 1: if (rev) list.SortItems(sort_name_r, (LONG)&theLGP);
		else list.SortItems(sort_name, (LONG)&theLGP);
		break;
	case 2: if (rev) list.SortItems(sort_type_r, (LONG)&theLGP);
		else list.SortItems(sort_type, (LONG)&theLGP);
		break;
	case 3: if (rev) list.SortItems(sort_size_r, (LONG)&theLGP);
		else list.SortItems(sort_size, (LONG)&theLGP);
		break;
	default: break;
	}
*/
}

void CIndexBar::OnDrawItem(UINT nIDCtrl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{

}

CTreeCtrl * CIndexBar::GetDirBox()
{
	if (!dirbox.m_hWnd) return NULL;
	return &dirbox;
}

//DEL void CIndexBar::OnDecompile() 
//DEL {
//DEL 
//DEL 
//DEL }

void CIndexBar::Update()
{
	dirbox.DeleteAllItems();
	HTREEITEM hroot[2049];
	hroot[0] = dirbox.InsertItem(theProject.GetName(),0,0);
	dirbox.SetItemData(hroot[0],(DWORD)-1);

	for (int i=0;(UINT)i<theProject.nDirs;i++) {
		hroot[i+1] = dirbox.InsertItem(theProject.GetDirName(i),1,2,hroot[(USHORT)(theProject.GetDirParent(i)+1)]);
		dirbox.SetItemData(hroot[i+1],i);
	}

	list.EnableWindow(TRUE);

}

void CIndexBar::OnClickDir(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMTREEVIEWA *pNM = (NMTREEVIEW*)pNMHDR;

	if (!dirbox.GetSelectedItem()) return;
	if (!pNM->itemNew.hItem) return;

	list.DeleteAllItems();

	if (pNM->itemNew.lParam == (DWORD)-1) return;

	CString dir1 = "";
	
	HTREEITEM hroot[32];
	int n=1;
	dir1.Insert(0,dirbox.GetItemText(pNM->itemNew.hItem));
	hroot[0] = pNM->itemNew.hItem;
	while (1) {
		hroot[n] = dirbox.GetParentItem(hroot[n-1]);
		if (dirbox.GetItemData(hroot[n]) == (DWORD)-1) break;
		dir1.Insert(0,"\\");
		dir1.Insert(0,dirbox.GetItemText(hroot[n]));
		n++;
	}

	CString dir2 = "";
	char buf[100];
	int q;
	int tmp;
	for (int i=0;(UINT)i<theProject.nFiles;i++) {
		dir2 = theProject.GetFileName(i);
		q = dir2.ReverseFind('\\');
		if (q < 0) continue;
		memset(buf,0,100);
		strncpy(buf,dir2,q);
		if (!stricmp(dir1,buf)) {
			int o, img;
			o = dir2.ReverseFind('.');
			     if (!strnicmp(".msd",(LPCTSTR)dir2+o,4)) img = 9;
			else if (!strnicmp(".tex",(LPCTSTR)dir2+o,4)) img = 4;
			else if (!strnicmp(".lzs",(LPCTSTR)dir2+o,4)) img = 4;
			else if (!strnicmp(".tim",(LPCTSTR)dir2+o,4)) img = 4;
			else img = 3;
			tmp = list.InsertItem(i,(LPCTSTR)dir2+q+1,img);
			list.SetItemText(tmp,1,"-");
			list.SetItemData(tmp,i);
		}
	}

	*pResult = 0;
}
