// EditorText.cpp: implementation of the CEditorText class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Garden.h"
#include "editors.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif





// Table of character widths

static const char *chColors[] = {
	"Disabled",
	"Dark",
	"Yellow",
	"Red",
	"Green",
	"Blue",
	"Purple",
	"White (standard)",
	"Disabled (flashing)",
	"Dark (flashing)",
	"Yellow (flashing)",
	"Red (flashing)",
	"Green (flashing)",
	"Blue (flashing)",
	"Purple (flashing)",
	"White (flashing)",
};

static const COLORREF clrColors[] = {
	RGB(0,0,0),
	RGB(0,0,0),
	RGB(255,255,0),
	RGB(255,0,0),
	RGB(0,255,0),
	RGB(0,128,255),
	RGB(255,0,255),
	RGB(255,255,255),
	RGB(0,0,0),
	RGB(0,0,0),
	RGB(255,255,0),
	RGB(255,0,0),
	RGB(0,255,0),
	RGB(0,128,255),
	RGB(255,0,255),
	RGB(255,255,255),
};

static BYTE chWidth[210] = {
	4,	8,	8,	8,	8,	8,	8,	8,	8,	8,
	8,	11,	7,	4,	5,	7,	10,	7,	7,	7,
	9,	9,	6,	6,	5,	6,	4,	4,	4,	9,
	7,	7,	4,	9,	7,	4,	9,	8,	8,	8,
	8,	8,	8,	8,	8,	5,	7,	8,	7,	9,
	8,	8,	8,	9,	8,	8,	9,	8,	9,	9,
	9,	9,	9,	8,	7,	7,	7,	7,	5,	7,
	7,	3,	5,	7,	3,	9,	7,	7,	7,	7,
	6,	7,	6,	7,	7,	7,	7,	8,	7,	8,
	8,	8,	8,	8,	8,	8,	8,	8,	5,	5,
	7,	7,	8,	8,	8,	8,	8,	8,	8,	8,
	8,	9,	7,	8,	8,	8,	8,	7,	7,	7,
	7,	7,	5,	5,	7,	7,	7,	7,	7,	7,
	7,	7,	7,	7,	7,	9,	12,	5,	5,	9,	// Careful with the 12s, might be larger
	9,	9,	6,	6,	9,	11,	7,	7,	9,	4,
	9,	9,	7,	11,	4,	7,	5,	5,	7,	12,	// Careful with the 12s, might be larger
	10,	10,	7,	9,	0,	7,	8,	7,	5,	9,	// The 0 is intentional, control code
	10,	10,	8,	8,	12,	8,	8,	8,	7,	8,	// Careful with the 12, might be 11, 4th from right might be 9
	8,	8,	8,	8,	8,	8,	12,	8,	8,	8,	// Careful with the 5th from left, unsure
	8,	8,	8,	8,	9,
						0,	0,	0,	0,	0,	// These are not used
	0,	0,	0,	0,	0,	0,	8,	8,	8,	8,	// Special codes used for editing

};


// Conversion of ASCII to FF8

static BYTE chFF8[256] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	' ', '.', '>', 'A', 'B', '+', '5', 'C',
	'8', '9', '4', '1', '<', '2', ';', ',',
	0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,
	0x29,0x2A,'-', 'µ', 'Ê', '3', 'Ë', '/',
	0x00,'E', 'F', 'G', 'H', 'I', 'J', 'K',
	'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
	'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[',
	'\\',']', '^', 0xA9,0x00,0xAA,0x00,'D',
	0x00,0x5F,0x60,0x61,0x62,0x63,0x64,0x65,
	0x66,0x67,0x68,0x69,0x6A,0x6B,0x6C,0x6D,
	0x6E,0x6F,0x70,0x71,0x72,0x73,0x74,0x75,
	0x76,0x77,0x78,'®', 0x00,'¯', 0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,'0', 0x00,0x00,
	0x00,0x00,0x00,0x00,0x8F,0x00,0x00,0x00,
	0x00,0x40,0x43,0x3F,0x3E,0x5A,0x00,0x30,
	0x00,0xC9,0x00,0x00,0xA7,0x00,0x00,0x00,
	0x00,0xBD,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0xC0,0x00,0x00,0xE2,0xB7,
	0xBC,0xC2,0x00,0x00,0xBA,0x00,0x00,0x00,
	0x00,0x00,0x00,0xC1,0x00,0x00,0x00,0xBE,
	0x79,0x7A,0x7B,0x00,0x7C,0x00,0x8F,0x7D,
	0x7E,0x7F,0x80,0x81,0x82,0x83,0x84,0x85,
	0x00,0x86,0x87,0x88,0x89,0x00,0x8A,0xB8,
	0x00,0x8B,0x8C,0x8D,0x8E,0x00,0x00,0x90,
	0x91,0x92,0x93,0x00,0x94,0x00,0xA7,0x95,
	0x96,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9D,
	0x00,0x9E,0x9F,0xA0,0xA1,0x00,0xA2,0x00,
	0x00,0xA3,0xA4,0xA5,0xA6,0x00,0x00,0x00
};

/////////////////////////////////////////////////////////////////////////////
// CFF8Edit


CFF8Edit::CFF8Edit()
{

	src = NULL;
	height = NULL;
	nLines = 0;

	bgbrush = CreateSolidBrush(RGB(32,32,32));
}

CFF8Edit::~CFF8Edit()
{
	if (height) free(height);

	DeleteObject(bgbrush);
}


BEGIN_MESSAGE_MAP(CFF8Edit, CListBox)
	//{{AFX_MSG_MAP(CFF8Edit)
	ON_WM_DRAWITEM_REFLECT()
	ON_WM_MEASUREITEM_REFLECT()
	ON_WM_CTLCOLOR_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFF8Edit message handlers


void CFF8Edit::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here
	if (!src || !height) return;

	CRect rc = lpDrawItemStruct->rcItem;
	CRect rcBounds = rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = rcBounds.Width();
	rc.bottom = rcBounds.Height();

	CDC dc, dcDest;
	dcDest.Attach(lpDrawItemStruct->hDC);
	dc.CreateCompatibleDC(&dcDest);

	CBitmap bmpTemp;
	bmpTemp.CreateCompatibleBitmap(&dcDest,rc.Width(),rc.Height());
	dc.SelectObject(&bmpTemp);

	dc.FillSolidRect(rc,RGB(32,32,32));

	if (lpDrawItemStruct->itemState & ODS_SELECTED)
		dc.FillSolidRect(rc.left+4,rc.top+4,rc.Width()-8,rc.Height()-8,RGB(128,128,128));
	else
		dc.FillSolidRect(rc.left+4,rc.top+4,rc.Width()-8,rc.Height()-8,RGB(64,64,64));
	
	int topframe = rc.top+2;
//	dc.Draw3dRect(rc.left+0,rc.top+0,rc.Width()-0,rc.Height()-0,RGB(32,32,32),RGB(32,32,32));
//	dc.Draw3dRect(rc.left+1,rc.top+1,rc.Width()-2,rc.Height()-2,RGB(32,32,32),RGB(32,32,32));

	rc.top += 9;

	COLORREF curcolor = CLR_NONE;
	UINT curflags = ILD_TRANSPARENT;

	int c = lpDrawItemStruct->itemData;
	int tab = 8;
	BYTE t;


	for (int i=0;(UINT)i<strlen(src[c]);i++) {
		t = src[c][i];

		if (t == 0x01) {
			rc.top += 19;
			dc.Draw3dRect(rc.left+2,topframe+0,rc.Width()-4,rc.top-topframe,RGB(128,128,128),RGB(0,0,0));
			dc.Draw3dRect(rc.left+3,topframe+1,rc.Width()-6,rc.top-topframe-2,RGB(192,192,192),RGB(32,32,32));
			topframe = rc.top;

			rc.top += 9;
			tab = 8;
			continue;
		}

		if (t == 0x02) {
			rc.top += 14;
			tab = 8;
			continue;
		}

		if (t == 0x03) {	// Character code
			i++;
			t = src[c][i];
			LPCTSTR name = CFF8Text::GetCharName(t);

			for (int j=0;j<strlen(name);j++) {
				t = name[j] - 0x20;
				il->DrawIndirect(&dc,t,CPoint(rc.left+tab,rc.top),CSize(chWidth[t],12),CPoint(0,0),curflags,SRCCOPY,CLR_NONE,curcolor);
				tab += chWidth[t];
			}
			continue;
		}

		if (t == 0x06) {		// Change color
			i++;
			t = src[c][i];
			curflags = ILD_TRANSPARENT | ILD_BLEND25;
			if (t == 0x27 || t == 0x2F)
				curflags = ILD_TRANSPARENT;
			curcolor = clrColors[t-0x20];
			if (t == 0x20 || t == 0x28)
				curcolor = CLR_NONE;

			continue;
		}

		if (t == 0x09) {		// Pause in text
			i++;
			tab += 4;
			continue;
		}

		if (t == 0x0E) {	// Name dictionary
			i++;
			t = src[c][i];
			LPCTSTR name = CFF8Text::GetLocationName(t);
			
			for (UINT j=0;j<strlen(name);j++) {
				t = name[j] - 0x20;
				il->DrawIndirect(&dc,t,CPoint(rc.left+tab,rc.top),CSize(chWidth[t],12),CPoint(0,0),curflags,SRCCOPY,CLR_NONE,curcolor);
				tab += chWidth[t];
			}
			continue;
		}


		if (t < 0x20 || t > 0xE2) continue;
		if (t == 0xAF)
			int v = 2;
		t -= 0x20;
		il->DrawIndirect(&dc,t,CPoint(rc.left+tab,rc.top),CSize(chWidth[t],12),CPoint(0,0),curflags,SRCCOPY,CLR_NONE,curcolor);
		tab += chWidth[t];
	}

	rc.top += 17;

	dc.Draw3dRect(rc.left+2,topframe+0,rc.Width()-4,rc.top-topframe,RGB(128,128,128),RGB(0,0,0));
	dc.Draw3dRect(rc.left+3,topframe+1,rc.Width()-6,rc.top-topframe-2,RGB(192,192,192),RGB(32,32,32));


	dcDest.BitBlt(rcBounds.left, rcBounds.top, rcBounds.Width(), rcBounds.Height(), &dc, 0, 0, SRCCOPY);

	dcDest.Detach();
	dc.DeleteDC();
	
}

void CFF8Edit::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here
	if (height)
		lpMeasureItemStruct->itemHeight = 14 + 14*height[lpMeasureItemStruct->itemData];
	else
		lpMeasureItemStruct->itemHeight = 14;

}


HBRUSH CFF8Edit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here
	return bgbrush;
}

//DEL void CFF8Edit::Init()
//DEL {
//DEL 	SetItemHeight(0,12);
//DEL }

int CFF8Edit::SetText(CString* _src, int lines)
{
	src = _src;

	nLines = lines;

	height = (int*)realloc(height,nLines*4);
	memset(height,0,nLines*4);


	size_t len;
	for (UINT i=0;i<nLines;i++) {
		height[i] = 1;
		len = strlen(src[i]);
		for (UINT j=0;j<len;j++) {
			if (((LPCTSTR)src[i])[j] == 0x01) height[i] += 2;
			if (((LPCTSTR)src[i])[j] == 0x02) height[i]++;
		}
	}

	ResetContent();
	for (i=0;i<nLines;i++) {
		AddString((LPCTSTR)i);
	}

	return nLines;
}







//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CEditorText, CChildFrame)

CEditorText::CEditorText()
{
	buf = NULL;
}

CEditorText::~CEditorText()
{
	if (buf) delete[] buf;
/*	if (buf) {
		for (int i=0;i<nLines;i++)
			if (buf[i]) free(buf[i]);
		free(buf);
	}*/
}



BEGIN_MESSAGE_MAP(CEditorText, CChildFrame)
	//{{AFX_MSG_MAP(CCompileSelect)
	ON_LBN_SELCHANGE(ID_EDITORTEXT_TEXT,OnSelChange)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()




int CEditorText::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CBitmap bmpTemp;
	il.Create(12,12,ILC_COLOR | ILC_MASK,0,210);

	bmpTemp.LoadBitmap(IDB_TEXT_FONT);
	il.Add(&bmpTemp,RGB(0,0,0));
	bmpTemp.DeleteObject();

	bmpTemp.LoadBitmap(IDB_TEXT_FONT1);
	il.Add(&bmpTemp,RGB(0,0,0));
	bmpTemp.DeleteObject();

	bmpTemp.LoadBitmap(IDB_TEXT_FONT2);
	il.Add(&bmpTemp,RGB(0,0,0));
	bmpTemp.DeleteObject();

	bmpTemp.LoadBitmap(IDB_TEXT_FONT3);
	il.Add(&bmpTemp,RGB(0,0,0));
	bmpTemp.DeleteObject();

	bmpTemp.LoadBitmap(IDB_TEXT_FONT4);
	il.Add(&bmpTemp,RGB(0,0,0));
	bmpTemp.DeleteObject();

	
	text.Create(/*WS_CHILD |*/ WS_VISIBLE | WS_VSCROLL | LBS_NOTIFY | LBS_OWNERDRAWVARIABLE,CRect(0,130,100,100),this,ID_EDITORTEXT_TEXT);
	text.ModifyStyleEx(0,WS_EX_CLIENTEDGE);
	text.il = &il;

	edit.Create(CRect(0,30,100,96),this,ID_EDITORTEXT_EDIT);
	edit.ModifyStyleEx(0,WS_EX_CLIENTEDGE);
	edit.il = &il;

	toolbar.Create(WS_VISIBLE | WS_CHILD | TBSTYLE_LIST | CCS_NOPARENTALIGN | CCS_NODIVIDER, CRect(0,3,500,24),this,ID_EDITORTEXT_TOOLBAR);
	toolbar.SetExtendedStyle(TBSTYLE_EX_DRAWDDARROWS);
	toolbar.AddStrings("Save\0 \0Update\0 \0Color\0Name\0Term\0 \0Table\0\0");
	TBBUTTON buttons[10];
	for (int i=0;i<9;i++) {
		buttons[i].bReserved[0] = 0;
		buttons[i].bReserved[1] = 0;
		buttons[i].dwData = 0;
		buttons[i].fsState = TBSTATE_ENABLED;
		buttons[i].fsStyle = TBSTYLE_BUTTON | TBSTYLE_AUTOSIZE;
		buttons[i].iBitmap = 0;
		buttons[i].idCommand = ID_EDITORTEXT_TOOLBAR + i;
		buttons[i].iString = i;
	}
	buttons[1].fsStyle = TBSTYLE_SEP;
	buttons[3].fsStyle = TBSTYLE_SEP;
//	buttons[4].fsStyle = TBSTYLE_DROPDOWN;
//	buttons[5].fsStyle = TBSTYLE_DROPDOWN;
//	buttons[6].fsStyle = TBSTYLE_DROPDOWN;
	buttons[7].fsStyle = TBSTYLE_SEP;
//	buttons[8].fsStyle = TBSTYLE_DROPDOWN;
	toolbar.AddButtons(9,buttons);
	toolbar.SetBitmapSize(CSize(0,16));


	m_bAutoMenuEnable = FALSE;
	mnuDrop.LoadMenu(IDR_EDITORTEXT_TOOLMENU);
	CMenu *mnu = mnuDrop.GetSubMenu(0);
	mnu->DeleteMenu(0,MF_BYPOSITION);
	for (i=0;i<16;i++) {
		mnu->AppendMenu(MF_OWNERDRAW,0x1000+i,(LPCTSTR)i);
	}

	mnu = mnuDrop.GetSubMenu(1);
	mnu->DeleteMenu(0,MF_BYPOSITION);
	mnu->AppendMenu(MF_OWNERDRAW,0x2000,(LPCTSTR)0);
	mnu->AppendMenu(MF_OWNERDRAW,0x2001,(LPCTSTR)1);
	mnu->AppendMenu(MF_OWNERDRAW,0x2002,(LPCTSTR)2);
	mnu->AppendMenu(MF_OWNERDRAW,0x2003,(LPCTSTR)3);
	mnu->AppendMenu(MF_OWNERDRAW,0x2004,(LPCTSTR)4);
	mnu->AppendMenu(MF_OWNERDRAW,0x2005,(LPCTSTR)5);
	mnu->AppendMenu(MF_OWNERDRAW,0x2006,(LPCTSTR)6);
	mnu->AppendMenu(MF_OWNERDRAW,0x2007,(LPCTSTR)7);
	mnu->AppendMenu(MF_OWNERDRAW,0x2008,(LPCTSTR)8);
	mnu->AppendMenu(MF_OWNERDRAW,0x2009,(LPCTSTR)9);
	mnu->AppendMenu(MF_OWNERDRAW,0x200A,(LPCTSTR)10);
	mnu->AppendMenu(MF_OWNERDRAW,0x200C,(LPCTSTR)12);
	mnu->AppendMenu(MF_OWNERDRAW,0x200D,(LPCTSTR)13);
	mnu->AppendMenu(MF_OWNERDRAW,0x200E,(LPCTSTR)14);
	mnu->AppendMenu(MF_OWNERDRAW,0x200F,(LPCTSTR)15);

	mnu = mnuDrop.GetSubMenu(2);
	mnu->DeleteMenu(0,MF_BYPOSITION);
	for (i=0;i<0x20;i++) {
		mnu->AppendMenu(MF_OWNERDRAW,0x3000+i,(LPCTSTR)i);
	}
	
	mnu = mnuDrop.GetSubMenu(3);
	mnu->DeleteMenu(0,MF_BYPOSITION);
	DWORD flags = 0;
	for (i=0;i<200;i++) {
		flags = MF_OWNERDRAW;
		if (i%20 == 0 && i != 0) flags |= MF_MENUBREAK;
		if (((i%20 * 10)+(i/20)) > 0xC2) flags |= MF_DISABLED;
		mnu->AppendMenu(flags,0x4000+(i%20 * 10)+(i/20),(LPCTSTR)(i%20 * 10)+(i/20));
//		if (i%20 == 19) {
//			mnu->AppendMenu(MF_MENUBARBREAK,0x4FFF,(LPCTSTR)0);
//		}
	}
//	mnu->DeleteMenu(21,MF_BYPOSITION);
	

	return 0;
}

void CEditorText::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDCtl != 0) {
		CChildFrame::OnDrawItem(nIDCtl,lpDrawItemStruct);
		return;
	}
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	CRect rc = lpDrawItemStruct->rcItem;

	if (lpDrawItemStruct->itemState & ODS_SELECTED)
		dc.FillSolidRect(rc,RGB(128,128,128));
	else
		dc.FillSolidRect(rc,RGB(64,64,64));

	int tab = 5;
	int i,t,c = lpDrawItemStruct->itemData;
	if (lpDrawItemStruct->itemID < 0x2000) {
		for (i=0;(UINT)i<strlen(chColors[c]);i++) {
			t = chFF8[chColors[c][i]]-0x20;
			if (c == 7 || c == 15)
				il.DrawIndirect(&dc,t,CPoint(rc.left+tab,rc.top+1),CSize(12,12),CPoint(0,0),ILD_TRANSPARENT,SRCCOPY,CLR_DEFAULT,CLR_DEFAULT);
			else if (c == 0 || c == 8)
				il.DrawIndirect(&dc,t,CPoint(rc.left+tab,rc.top+1),CSize(12,12),CPoint(0,0),ILD_TRANSPARENT | ILD_BLEND25,SRCCOPY,CLR_NONE,CLR_NONE);
			else
				il.DrawIndirect(&dc,t,CPoint(rc.left+tab,rc.top+1),CSize(12,12),CPoint(0,0),ILD_TRANSPARENT | ILD_BLEND25,SRCCOPY,CLR_DEFAULT,clrColors[c]);
			tab += chWidth[t];
		}
	}
	else if (lpDrawItemStruct->itemID < 0x3000) {
		LPCTSTR name = edit.GetCharName(c+0x30);
		for (i=0;(UINT)i<strlen(name);i++) {
			il.DrawIndirect(&dc,name[i]-0x20,CPoint(rc.left+tab,rc.top+1),CSize(12,12),CPoint(0,0),ILD_TRANSPARENT|ILD_BLEND25,SRCCOPY,CLR_DEFAULT,RGB(255,128,0));
			tab += chWidth[name[i]-0x20];
		}
	}
	else if (lpDrawItemStruct->itemID < 0x4000) {
		LPCTSTR name = edit.GetLocationName(c+0x20);
		for (i=0;(UINT)i<strlen(name);i++) {
			il.DrawIndirect(&dc,name[i]-0x20,CPoint(rc.left+tab,rc.top+1),CSize(12,12),CPoint(0,0),ILD_TRANSPARENT|ILD_BLEND25,SRCCOPY,CLR_DEFAULT,RGB(64,0,255));
			tab += chWidth[name[i]-0x20];
		}
	}
	else if (lpDrawItemStruct->itemID < 0x5000) {
		il.DrawIndirect(&dc,lpDrawItemStruct->itemData,CPoint(rc.left+tab,rc.top),CSize(12,12),CPoint(0,0),ILD_TRANSPARENT,SRCCOPY,CLR_DEFAULT,CLR_DEFAULT);
	}

	dc.Detach();

}

void CEditorText::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDCtl != 0) {
		CChildFrame::OnMeasureItem(nIDCtl,lpMeasureItemStruct);
		return;
	}
	if (lpMeasureItemStruct->itemID < 0x2000) {
		lpMeasureItemStruct->itemWidth = 120;
		lpMeasureItemStruct->itemHeight = 14;
	}
	else if (lpMeasureItemStruct->itemID < 0x3000) {
		lpMeasureItemStruct->itemWidth = 120;
		lpMeasureItemStruct->itemHeight = 14;
	}
	else if (lpMeasureItemStruct->itemID < 0x4000) {
		lpMeasureItemStruct->itemWidth = 120;
		lpMeasureItemStruct->itemHeight = 14;
	}
	else if (lpMeasureItemStruct->itemID < 0x5000) {
		lpMeasureItemStruct->itemWidth = 12;
		lpMeasureItemStruct->itemHeight = 12;
	}
	
}


void CEditorText::OnSize(UINT nType, int cx, int cy)
{
	text.SetWindowPos(NULL,0,0,cx,cy-130,SWP_NOZORDER | SWP_NOMOVE);
	edit.SetWindowPos(NULL,0,0,cx,96,SWP_NOZORDER | SWP_NOMOVE);
	toolbar.UpdateWindow();
}


BOOL CEditorText::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (LOWORD(wParam) == ID_EDITORTEXT_TEXT) {
		if (HIWORD(wParam) & 1)
			OnSelChange();
	}
	CMenu *mnu = NULL;
	switch (wParam) {
	case ID_EDITORTEXT_TOOLBAR + 4:
		mnu = mnuDrop.GetSubMenu(0);
		break;
	case ID_EDITORTEXT_TOOLBAR + 5:
		mnu = mnuDrop.GetSubMenu(1);
		break;
	case ID_EDITORTEXT_TOOLBAR + 6:
		mnu = mnuDrop.GetSubMenu(2);
		break;
	case ID_EDITORTEXT_TOOLBAR + 8:
		mnu = mnuDrop.GetSubMenu(3);
		break;
	default:
		break;
	}
	if (mnu) {
		CRect rc;
		toolbar.GetRect(wParam,rc);
		toolbar.ClientToScreen(rc);
		mnu->TrackPopupMenu(TPM_RIGHTBUTTON,rc.left,rc.bottom,this);
		return FALSE;
	}

	if (wParam == ID_EDITORTEXT_TOOLBAR) {
		// Save
		file.SeekToBegin();
		int q = nLines*sizeof(int);
		for (int i=0;i<nLines;i++) {
			file.Write(&q,sizeof(int));
			q += strlen(buf[i])+1;
		}
		for (i=0;i<nLines;i++) {
			file.Write(buf[i],strlen(buf[i])+1);
		}
		file.SetLength(q);
		return FALSE;
	}
	if (wParam == ID_EDITORTEXT_TOOLBAR+2) {
		// Update
		int q = text.GetCurSel();
		buf[q] = edit.text;
		text.SetText(buf,nLines);
		text.SetCurSel(q);
		text.Invalidate();
		return FALSE;
	}
	
	
	char buf[200];
	if (wParam < 0x2000) {
		sprintf(buf,"\x06%c",0x20+(wParam & 0xFFF));
		edit.InsertString(buf);
	}
	else if (wParam < 0x3000) {
		sprintf(buf,"\x03%c",0x30+(wParam & 0xFFF));
		edit.InsertString(buf);
	}
	else if (wParam < 0x4000) {
		sprintf(buf,"\x0E%c",0x20+(wParam & 0xFFF));
		edit.InsertString(buf);
	}
	else if (wParam < 0x5000) {
		sprintf(buf,"%c",0x20+(wParam & 0xFFF));
		edit.InsertString(buf);
	}

//	return CChildFrame::OnCommand(wParam, lParam);
	return FALSE;
}


//DEL BOOL CEditorText::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
//DEL {
//DEL 	// TODO: Add your specialized code here and/or call the base class
//DEL 	if (wParam == ID_EDITORTEXT_TOOLBAR) {
//DEL 		NMTOOLBARA *pNM = (NMTOOLBAR*)lParam;
//DEL 		if (pNM->hdr.code == TBN_DROPDOWN) {
//DEL 			CMenu* pPopup = mnuDrop.GetSubMenu(0);
//DEL 			ASSERT(pPopup != NULL);
//DEL 			pPopup->TrackPopupMenu(TPM_RIGHTALIGN |
//DEL 				TPM_RIGHTBUTTON, 200, 100, this);
//DEL 
//DEL 			return FALSE;
//DEL 		}
//DEL 	}
//DEL 	return CWnd::OnNotify(wParam, lParam, pResult);
//DEL }


void CEditorText::LoadFile(CString strFile)
{
	CChildFrame::LoadFile(strFile);
	if ((HFILE)file == (UINT)-1) { MessageBox("Could not open file.","Garden",MB_ICONERROR); DestroyWindow(); return; }
	char dispbuf[200];
	strcpy(dispbuf,file.GetFileName());
	strcat(dispbuf," - Text editor");
	SetWindowText(dispbuf);

	int temp;
	file.Read(&temp,4);
	nLines = temp / 4;
	int *offsets = (int*)malloc(temp);
	offsets[0] = temp;
	file.Read(&offsets[1],temp-4);

	char *src = (char*)malloc(file.GetLength()-temp);
	//buf = (BYTE**)malloc(nLines*sizeof(BYTE*));
	buf = new CString[nLines];
	//memset(buf,0,nLines*sizeof(BYTE*));
	file.Read(src,file.GetLength()-temp);
	for (int i=0;i<nLines;i++) {
//		buf[i] = (BYTE*)malloc(strlen(src+offsets[i]-temp)+1);
//		strcpy((char*)buf[i],src+offsets[i]-temp);
		buf[i] = (LPCTSTR)(src+offsets[i]-temp);
	}
	text.SetText(buf,nLines);

	free(offsets);
	free(src);

	text.SetCurSel(0);
	edit.SetText((LPCTSTR)buf[0]);

}

BOOL CEditorText::PreCreateWindow(CREATESTRUCT &cs)
{
	if ( !CChildFrame::PreCreateWindow(cs) )
		return FALSE;

	cs.cx = 400;
	cs.cy = 400;

	return TRUE;
}

void CEditorText::OnSelChange()
{
	if (text.GetSelCount()==0) return;
	edit.SetText((LPCTSTR)buf[text.GetCurSel()]);

}








/////////////////////////////////////////////////////////////////////////////
// CFF8Text

CFF8Text::CFF8Text()
{
	bgbrush = CreateSolidBrush(RGB(32,32,32));
	topoffset = 0;
	curpos = 0;
	caretpos = CPoint(7,8);
//	memset(text,0,0x2000);
	text = "";
}

CFF8Text::~CFF8Text()
{
	DeleteObject(bgbrush);
}


BEGIN_MESSAGE_MAP(CFF8Text, CWnd)
	//{{AFX_MSG_MAP(CFF8Text)
	ON_WM_PAINT()
	ON_WM_VSCROLL()
	ON_WM_MOUSEACTIVATE()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CFF8Text message handlers


BOOL CFF8Text::Create(const RECT& rect, CWnd* pParentWnd, UINT nID) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CWnd::Create(AfxRegisterWndClass(0,LoadCursor(NULL,IDC_IBEAM),bgbrush,NULL),"GardenFF8Edit",WS_VISIBLE | WS_CHILD | WS_VSCROLL | WS_TABSTOP,rect,pParentWnd,nID);

}

void CFF8Text::SetText(LPCTSTR src)
{
//	memset(text,0,0x2000);
//	strcpy((LPSTR)text,src);
	text = src;

	CalcHeight();

	topoffset = 0;
	curpos = 0;
	caretpos = CPoint(7,8);
	Invalidate();

}

void CFF8Text::OnPaint() 
{
	CPaintDC dcDest(this); // device context for painting
	
	if (*(LPCTSTR)text == 0) return;

	// TODO: Add your message handler code here
	CRect rc;
	GetClientRect(rc);
	rc.top = -(topoffset * 14);
	rc.bottom = rc.top + (height * 14);

	
	CRect rcBounds = rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = rcBounds.Width();
	rc.bottom = rcBounds.Height();

	CDC dc;
	dc.CreateCompatibleDC(&dcDest);

	CBitmap bmpTemp;
	bmpTemp.CreateCompatibleBitmap(&dcDest,rc.Width(),rc.Height());
	dc.SelectObject(&bmpTemp);

	dc.FillSolidRect(rc,RGB(32,32,32));

	dc.FillSolidRect(rc.left+4,rc.top+4,rc.Width()-8,rc.Height()-8,RGB(64,64,64));
	
	int topframe = rc.top+2;
//	dc.Draw3dRect(rc.left+0,rc.top+0,rc.Width()-0,rc.Height()-0,RGB(32,32,32),RGB(32,32,32));
//	dc.Draw3dRect(rc.left+1,rc.top+1,rc.Width()-2,rc.Height()-2,RGB(32,32,32),RGB(32,32,32));

	rc.top += 9;

	COLORREF curcolor = CLR_NONE;
	UINT curflags = ILD_TRANSPARENT;

//	int c = lpDrawItemStruct->itemData;
	int tab = 8;
	BYTE t;

	BYTE *p = (BYTE*)(LPCTSTR)text;

	BOOL color = FALSE,			// Next char is a color code
		 charname = FALSE,		// Next char is a character name code
		 location = FALSE,		// Next char is a game term code
	     pausetime = FALSE;		// Next char is a pause length

	while (*p) {
		t = *p++;

		if (t == 0x01) {
			rc.top += 19;
			dc.Draw3dRect(rc.left+2,topframe+0,rc.Width()-4,rc.top-topframe,RGB(128,128,128),RGB(0,0,0));
			dc.Draw3dRect(rc.left+3,topframe+1,rc.Width()-6,rc.top-topframe-2,RGB(192,192,192),RGB(32,32,32));
			topframe = rc.top;

			rc.top += 9;
			tab = 8;
			continue;
		}

		if (t == 0x02) {
			rc.top += 14;
			tab = 8;
			continue;
		}

		if (t == 0x03) {	// Character code
			t = 207;
			il->DrawIndirect(&dc,t,CPoint(rc.left+tab,rc.top),CSize(chWidth[t],12),CPoint(0,0),ILD_TRANSPARENT | ILD_BLEND25,SRCCOPY,CLR_NONE,RGB(255,128,0));
			tab += chWidth[t];
			charname = TRUE;
			continue;
		}

		if (charname) {
			CString name = GetCharName(t);
			for (int j=0;(UINT)j<strlen(name);j++) {
				t = name[j] - 0x20;
				il->DrawIndirect(&dc,t,CPoint(rc.left+tab,rc.top),CSize(chWidth[t],12),CPoint(0,0),ILD_TRANSPARENT | ILD_BLEND25,SRCCOPY,CLR_NONE,RGB(255,128,0));
				tab += chWidth[t];
			}			
			charname = FALSE;
			continue;
		}

		if (t == 0x06) {		// Change color
			t = *p;
			curflags = ILD_TRANSPARENT | ILD_BLEND25;
			if (t == 0x27 || t == 0x2F)
				curflags = ILD_TRANSPARENT;
			curcolor = clrColors[t-0x20];
			if (t == 0x20 || t == 0x28)
				curcolor = CLR_NONE;

			t = 209;
			il->DrawIndirect(&dc,t,CPoint(rc.left+tab,rc.top),CSize(chWidth[t],12),CPoint(0,0),curflags,SRCCOPY,CLR_NONE,curcolor);
			tab += chWidth[t];

			continue;
		}

		if (t == 0x09) {		// Pause in text
			t = 206;
			il->DrawIndirect(&dc,t,CPoint(rc.left+tab,rc.top),CSize(chWidth[t],12),CPoint(0,0),curflags,SRCCOPY,CLR_NONE,curcolor);
			tab += chWidth[t];
			pausetime = TRUE;
			continue;
		}

		if (pausetime) {
			char tempbuf[4];
			sprintf(tempbuf,"%02X", t);
			for (int j=0;j<2;j++) {
				t = (tempbuf[j] < 'A') ? (tempbuf[j] - 0x2F) : (tempbuf[j] - 28);
				il->DrawIndirect(&dc,t,CPoint(rc.left+tab,rc.top),CSize(chWidth[t],12),CPoint(0,0),ILD_TRANSPARENT | ILD_BLEND25,SRCCOPY,CLR_NONE,RGB(255,128,0));
				tab += chWidth[t];
			}			
			pausetime = FALSE;
			continue;
		}

		if (t == 0x0E) {	// Name dictionary
			t = 208;
			il->DrawIndirect(&dc,t,CPoint(rc.left+tab,rc.top),CSize(chWidth[t],12),CPoint(0,0),ILD_TRANSPARENT | ILD_BLEND25,SRCCOPY,CLR_NONE,RGB(64,0,255));
			tab += chWidth[t];
			location = TRUE;
			continue;
		}

		if (location) {
			CString name = GetLocationName(t);
			for (int j=0;(UINT)j<strlen(name);j++) {
				t = name[j] - 0x20;
				il->DrawIndirect(&dc,t,CPoint(rc.left+tab,rc.top),CSize(chWidth[t],12),CPoint(0,0),ILD_TRANSPARENT | ILD_BLEND25,SRCCOPY,CLR_NONE,RGB(64,0,255));
				tab += chWidth[t];
			}


			location = FALSE;
			continue;
		}


		if (t < 0x20 || t > 0xE2) continue;
		if (t == 0xAF)
			int v = 2;
		t -= 0x20;
		il->DrawIndirect(&dc,t,CPoint(rc.left+tab,rc.top),CSize(chWidth[t],12),CPoint(0,0),curflags,SRCCOPY,CLR_NONE,curcolor);
		tab += chWidth[t];
	}

	rc.top += 17;

	dc.Draw3dRect(rc.left+2,topframe+0,rc.Width()-4,rc.top-topframe,RGB(128,128,128),RGB(0,0,0));
	dc.Draw3dRect(rc.left+3,topframe+1,rc.Width()-6,rc.top-topframe-2,RGB(192,192,192),RGB(32,32,32));


	dcDest.BitBlt(rcBounds.left, rcBounds.top, rcBounds.Width(), rcBounds.Height(), &dc, 0, 0, SRCCOPY);

	dc.DeleteDC();
	
	

}

void CFF8Text::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// Scroll the text view
	int prev = topoffset;
	switch (nSBCode) {
	case SB_BOTTOM:
		topoffset = max(0,height-6);
		break;
	case SB_ENDSCROLL:
		break;
	case SB_LINEDOWN:
		topoffset++;
		if (topoffset > height-6) topoffset = height-6;
		break;
	case SB_LINEUP:
		topoffset--;
		if (topoffset < 0) topoffset = 0;
		break;
	case SB_PAGEDOWN:
		topoffset += 6;
		if (topoffset > height-6) topoffset = height-6;
		break;
	case SB_PAGEUP:
		topoffset -= 6;
		if (topoffset < 0) topoffset = 0;
		break;
	case SB_THUMBPOSITION:
		topoffset = nPos;
		break;
	case SB_THUMBTRACK:
		break;
	case SB_TOP:
		topoffset = 0;
		break;
	default:
		break;
	}
	
	if (prev != topoffset) {
		SetScrollPos(SB_VERT,topoffset);
		MoveCursor(curpos);

		Invalidate();
	}
	
//	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CFF8Text::OnSetFocus(CWnd* pOldWnd) 
{
//	CWnd::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
	CreateSolidCaret(2,13);
	SetCaretPos(caretpos);
	ShowCaret();

}

void CFF8Text::OnKillFocus(CWnd* pNewWnd) 
{
//	CWnd::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
	DestroyCaret();

}


int CFF8Text::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
	SetFocus();
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}


void CFF8Text::MoveCursor(int pos)
{
	if (pos<0) return;
	if ((UINT)pos>strlen(text)) return;

	int len = pos;
//	int newpos = 0;
	caretpos.x = 7;
	caretpos.y = 8;
//	int newoffset = 0;

	BYTE *p = (BYTE*)(LPCTSTR)text;
	LPCTSTR name;
	UINT i;

	BOOL color = FALSE,			// Next char is a color code
		 charname = FALSE,		// Next char is a character name code
		 location = FALSE,		// Next char is a game term code
		 pausetime = FALSE;


	while (len-- > 0 /*p != ((BYTE*)(LPCTSTR)text + pos)*/) {
		if (*p == 0) break;
		if (charname) {
			name = GetCharName(*p);
			for (i=0;i<strlen(name);i++)
				caretpos.x += chWidth[name[i]-0x20];
			charname = FALSE;
		} else if (pausetime) {
			caretpos.x += 16;
			pausetime = FALSE;
		} else if (location) {
			name = GetLocationName(*p);
			for (i=0;i<strlen(name);i++)
				caretpos.x += chWidth[name[i]-0x20];
			location = FALSE;
		} else {
			switch (*p) {
			case 0x01:
				caretpos.x = 7;
				caretpos.y += 28;
				break;
			case 0x02:
				caretpos.x = 7;
				caretpos.y += 14;
				break;
			case 0x03:
				caretpos.x += chWidth[207];
				charname = TRUE;
				break;
			case 0x06:
				caretpos.x += chWidth[209];
				break;
			case 0x09:
				caretpos.x += chWidth[206];
				pausetime = TRUE;
				break;
			case 0x0E:
				caretpos.x += chWidth[208];
				location = TRUE;
				break;
			default:
				caretpos.x += chWidth[*p-0x20];
				break;
			}
		}
		p++;

	}

	caretpos.y -= 14 * topoffset;

/*	CRect rc;
	GetClientRect(rc);
	if (caretpos.y < 0) {
		caretpos.y = 8;
		OnVScroll(SB_THUMBPOSITION,newoffset,NULL);
	}
	if (caretpos.y > rc.bottom - 14) {
		caretpos.y = 8;
		OnVScroll(SB_THUMBPOSITION,newoffset,NULL);
	}
*/
	SetCaretPos(caretpos);
	curpos = pos;
}

LPCTSTR CFF8Text::GetCharName(int code)
{
	LPCTSTR name;
	switch (code) {
	case 0x30: name = "Wos_jj";  break;	// Squall
	case 0x31: name = "^cjj";    break;	// Zell
	case 0x32: name = "Mptglc";  break;	// Irvine
	case 0x33: name = "Usgqrgq"; break;	// Quistis
	case 0x34: name = "Vglm_";   break;	// Rinoa
	case 0x35: name = "Wcjnfgc"; break;	// Selphie
	case 0x36: name = "Wcgdcp";  break;	// Seifer
	case 0x37: name = "Ibc_";    break;	// Edea
	case 0x38: name = "P_esl_";  break;	// Laguna
	case 0x39: name = "Ogpmq";   break;	// Kiros
	case 0x3A: name = "[_pb";    break;	// Ward
//	case 0x3B: name = "";        break;	// --- none
	case 0x3C: name = "Kpgctcp"; break;	// Griever
	case 0x3D: name = "Qme";     break;	// Mog
	case 0x3E: name = "Gfmam`m"; break;	// Chocobo
	case 0x3F: name = "Elecjm";  break;	// Angelo
	default: name = ""; break;
	}
	return name;
}

LPCTSTR CFF8Text::GetLocationName(int code)
{
	LPCTSTR name;
	switch (code) {
	case 0x20: name = "K_j`_bg_";				break;	// Galbadia
	case 0x21: name = "Iqrf_p";					break;	// Esthar
	case 0x22: name = "F_j_k`";					break;	// Balamb
	case 0x23: name = "Hmjjcr";					break;	// Dollet
	case 0x24: name = "Xgk`cp";					break;	// Timber
	case 0x25: name = "Xp_`g_";					break;	// Trabia
	case 0x26: name = "Gclrp_";					break;	// Centra
	case 0x27: name = "Jgqfcpk_lq Lmpgxml";		break;	// Fishermans Horizon
	case 0x28: name = "I_qr Ea_bckw";			break;	// East Academy
	case 0x29: name = "Hcqcpr Tpgqml";			break;	// Desert Prison
	case 0x2A: name = "Xp_`g_ K_pbcl";			break;	// Trabia Garden
	case 0x2B: name = "Psl_p F_qc";				break;	// Lunar Base
	case 0x2C: name = "Wfskg Zgjj_ec";			break;	// Shumi Village
	case 0x2D: name = "Hcjgle Ggrw";			break;	// Deling City
	case 0x2E: name = "F_j_k` K_pbcl";			break;	// Balamb Garden
	case 0x2F: name = "I_qr Ea_bckw Wr_rgml";	break;	// East Academy Station
	case 0x30: name = "Hmjjcr Wr_rgml";			break;	// Dollet Station
	case 0x31: name = "Hcqcpr Tpgqml Wr_rgml";	break;	// Desert Prison Station
	case 0x32: name = "Psl_p K_rc";				break;	// Lunar Gate

	case 0x33: name = "Vcqrmpcq";				break;	// Restores
	case 0x34: name = "qr_rsq";					break;	// status
	case 0x35: name = "jc_plq";					break;	// learns
	case 0x36: name = "_`gjgrw";				break;	// ability
	case 0x37: name = "Q_ega";					break;	// Magic
	case 0x38: name = "Vcdglc";					break;	// Refine
	case 0x39: name = "Nslargmlq";				break;	// Junctions
	case 0x3A: name = "V_gqcq";					break;	// Raises
	case 0x3B: name = "amkk_lb";				break;	// command
	case 0x3C: name = "Q_e_xglc";				break;	// Magazine
	case 0x3D: name = "Yjrgkcag_ G_qrjc";		break;	// Ultimecia Castle
	case 0x3E: name = "K_pbcl";					break;	// Garden
	case 0x3F: name = "Hcjgle";					break;	// Deling
	
	default: name = ""; break;
	}
	return name;
}

void CFF8Text::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
//	TRACE("%X\n",nChar);
	HideCaret();

	switch (nChar) {
	
	case 0x08:		// Back-space
		if (curpos == 0) break;
		text.Delete(curpos-1);
		MoveCursor(curpos-1);
		break;
	
	case 0x0D:		// Return
		if (GetKeyState(VK_SHIFT) & 0x80)	// Check if Shift+Return
			text.Insert(curpos,(TCHAR)0x01);	// Page break
		else
			text.Insert(curpos,(TCHAR)0x02);	// Line break
		MoveCursor(curpos+1);
		break;
	
	default:
		if (nChar == '"') {
			BYTE *p = (BYTE*)(LPCTSTR)text;
			BYTE *pcur = p + curpos;
			int c = 0;
			while (p != pcur) {
				if (*p == 0x3F || *p == 0x3E) c++;
				p++;
			}
			if (c % 2)
				text.Insert(curpos,0x3E);
			else
				text.Insert(curpos,0x3F);
			MoveCursor(curpos+1);

		} else {
			if (chFF8[nChar] != 0) {
				text.Insert(curpos,(TCHAR)chFF8[nChar]);
				MoveCursor(curpos+1);
			}
		}

	}
	
	CalcHeight();
	Invalidate();
	ShowCaret();

}


void CFF8Text::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	HideCaret();

//	TRACE("%X\n",nChar);
	BYTE *p = (BYTE*)(LPCTSTR)text + curpos;
	int i = 0;
	switch (nChar) {
		
	case VK_END:			// End
		while (*p++ > 0x02) {
			i++;
		}
		MoveCursor(curpos+i);
		break;
	
	case VK_HOME:			// Home
		if (curpos == 0) break;
		while (*--p > 0x02) {
			i++;
			if (p == (BYTE*)(LPCTSTR)text) break;
		}
		MoveCursor(curpos-i);
		break;
	
	case VK_LEFT:			// Left key
		MoveCursor(curpos-1);
		break;

	case VK_UP:				// Up key
		if (curpos == 0) break;
		while (*--p > 0x02) {
			i++;
			if (p == (BYTE*)(LPCTSTR)text) break;
		}
		while (*--p > 0x02) {
			i++;
			if (p == (BYTE*)(LPCTSTR)text) break;
		}
		MoveCursor(curpos-i-1);
		break;

	case VK_RIGHT:			// Right key
		MoveCursor(curpos+1);
		break;

	case VK_DOWN:			// Down key
		while (*p++ > 0x02) {
			i++;
		}
		MoveCursor(curpos+i+1);
		break;

	case VK_DELETE:
		text.Delete(curpos);
		CalcHeight();
		Invalidate();
		break;

	default:
		break;
	}

	ShowCaret();
//	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CFF8Text::CalcHeight()
{
	BYTE *p = (BYTE*)(LPCTSTR)text;
	height = 2;
	while (*p) {
		if (*p == 0x01) height += 2;
		if (*p == 0x02) height++;
		p++;
	}

	SetScrollRange(SB_VERT,0,height-6);

}



void CFF8Text::InsertString(LPCTSTR str)
{
	text.Insert(curpos,str);
	MoveCursor(curpos+strlen(str));
	Invalidate();
}
