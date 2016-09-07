// EditorTexture.cpp: implementation of the CEditorTexture class.
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

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CEditorTexture, CChildFrame)

CEditorTexture::CEditorTexture()
{

}

CEditorTexture::~CEditorTexture()
{

}

void CEditorTexture::LoadFile(CString strFile)
{
	CChildFrame::LoadFile(strFile);
	if ((HFILE)file == (UINT)-1) { MessageBox("Could not open file.","Garden",MB_ICONERROR); DestroyWindow(); return; }
	char dispbuf[200];
	strcpy(dispbuf,file.GetFileName());
	strcat(dispbuf," - Texture editor");
	SetWindowText(dispbuf);

	int o = strFile.ReverseFind('.');
	LPCTSTR suffix = (LPCTSTR)strFile+o;

	     if (!strnicmp(".tex",suffix,4)) type = 0;
	else if (!strnicmp(".lzs",suffix,4)) type = 1;
	else if (!strnicmp(".tim",suffix,4)) type = 2;
	else return;

	CDC destDC;
	BITMAPINFO *bmi = NULL;
	bmpTexture.DeleteObject();

	iWidth = 0;
	iHeight = 0;
	iColors = 0;

	switch (type) {
	case 0:		// TEX
		file.Seek(0x3C,CFile::begin);
		file.Read(&iWidth,4);
		file.Read(&iHeight,4);
		file.Seek(0x58,CFile::begin);
		file.Read(&iColors,4);

		if (iColors == 0) {
			bmi = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER));
			bmi->bmiHeader.biBitCount = 16;
			bmi->bmiHeader.biCompression = BI_RGB; //BI_BITFIELDS;
			bmi->bmiHeader.biClrImportant = 0;
			bmi->bmiHeader.biClrUsed = 0;
			bmi->bmiHeader.biHeight = -iHeight;
			bmi->bmiHeader.biPlanes = 1;
			bmi->bmiHeader.biSize = sizeof(bmi->bmiHeader);
			bmi->bmiHeader.biSizeImage = 0; //iWidth*iHeight*2;
			bmi->bmiHeader.biWidth = iWidth;
			bmi->bmiHeader.biXPelsPerMeter = 72;
			bmi->bmiHeader.biYPelsPerMeter = 72;

	//		DWORD bitmasks[3] = { 0xF800, 0x07E0, 0x001F};
			// 0x7FFF
	//		memcpy(bmi->bmiColors, bitmasks, 12);

			WORD *bits = (WORD*)malloc(iWidth*iHeight*2);
			memset(bits,0,iWidth*iHeight*2);
			file.Seek(0xF0,CFile::begin);
			file.Read(bits,iWidth*iHeight*2);
			
			USHORT tmpFlip;
			for (int i=0;i<iWidth*iHeight;i++) {
				tmpFlip = (bits[i] & 0x7C00) >> 10;		// Red -> Blue
				tmpFlip |= (bits[i] & 0x07E0);			// Green -> Green
				tmpFlip |= (bits[i] & 0x001F) << 10;	// Blue -> Red
				bits[i] = tmpFlip;
			}
			
			bmpTexture.CreateCompatibleBitmap(m_Canvas.GetDC(),iWidth,iHeight);
			destDC.CreateCompatibleDC(m_Canvas.GetDC());
			SetDIBits((HDC)destDC,(HBITMAP)bmpTexture,0,iHeight,(void*)bits,bmi,DIB_RGB_COLORS);
			destDC.DeleteDC();

			free(bits);
		
		} else {

			bmi = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER)+4*iColors);

			bmi->bmiHeader.biBitCount = 8;
			bmi->bmiHeader.biClrImportant = 0;
			bmi->bmiHeader.biClrUsed = iColors;
			bmi->bmiHeader.biCompression = BI_RGB;
			bmi->bmiHeader.biHeight = -iHeight;
			bmi->bmiHeader.biPlanes = 1;
			bmi->bmiHeader.biSize = sizeof(bmi->bmiHeader);
			bmi->bmiHeader.biSizeImage = iWidth*iHeight;
			bmi->bmiHeader.biWidth = iWidth;
			bmi->bmiHeader.biXPelsPerMeter = 72;
			bmi->bmiHeader.biYPelsPerMeter = 72;

			file.Seek(0xF0,CFile::begin);
			file.Read(bmi->bmiColors,4*iColors);
			
			for (int i=0;i<iColors;i++) bmi->bmiColors[i].rgbReserved = 0;	// Make sure rgbReserved is zero

			char *bits = (char*)malloc(iWidth*iHeight);
			memset(bits,0,iWidth*iHeight);
			file.Read(bits,iWidth*iHeight);
			
			bmpTexture.CreateCompatibleBitmap(m_Canvas.GetDC(),iWidth,iHeight);
			destDC.CreateCompatibleDC(m_Canvas.GetDC());
			SetDIBits((HDC)destDC,(HBITMAP)bmpTexture,0,iHeight,(void*)bits,bmi,DIB_RGB_COLORS);
			destDC.DeleteDC();
			free(bits);
		}

//		SetWindowPos(NULL,0,0,max(200,iWidth+30),max(100,iHeight+75),SWP_NOMOVE | SWP_NOZORDER);

		break;

	case 1:		// LZS (screen)
//		CFF8Archive ff8;
//		ff8.InflateFile(&temp,&file,NULL);

		break;

	case 2:		// TIM
		short nPalettes, iPalSize;
		iColors = 256;
		bmi = (BITMAPINFO*)malloc(sizeof(BITMAPINFOHEADER)+4*iColors);

		file.Seek(0x10,CFile::begin);
		file.Read(&iPalSize,2);
		file.Read(&nPalettes,2);
		WORD *pal = (WORD*)malloc(2*iPalSize);
		file.Read(pal,2*iPalSize);
		for (int i=0;i<256;i++) {
			bmi->bmiColors[i].rgbRed = (pal[i] & 0x001F) << 3;
			bmi->bmiColors[i].rgbGreen = (pal[i] & 0x03E0) >> 2;
			bmi->bmiColors[i].rgbBlue = (pal[i] & 0x7C00) >> 7;
			bmi->bmiColors[i].rgbReserved = 0;
		}
		free(pal);

		file.Seek(iPalSize*(nPalettes-1)*2,CFile::current);

		int size;
		file.Read(&size,4);
		file.Seek(0x2,CFile::current);
		file.Read(&iHeight,2);
		iWidth = (size - 0xC) / iHeight;
		file.Seek(0x4,CFile::current);

		bmi->bmiHeader.biBitCount = 8;
		bmi->bmiHeader.biClrImportant = 0;
		bmi->bmiHeader.biClrUsed = iColors;
		bmi->bmiHeader.biCompression = BI_RGB;
		bmi->bmiHeader.biHeight = -iHeight;
		bmi->bmiHeader.biPlanes = 1;
		bmi->bmiHeader.biSize = sizeof(bmi->bmiHeader);
		bmi->bmiHeader.biSizeImage = size - 0xC;
		bmi->bmiHeader.biWidth = iWidth;
		bmi->bmiHeader.biXPelsPerMeter = 72;
		bmi->bmiHeader.biYPelsPerMeter = 72;

		char *bits = (char*)malloc(size-0xC);
		memset(bits,0,size-0xC);
		file.Read(bits,size-0xC);
		
		bmpTexture.CreateCompatibleBitmap(m_Canvas.GetDC(),iWidth,iHeight);
		destDC.CreateCompatibleDC(m_Canvas.GetDC());
		SetDIBits((HDC)destDC,(HBITMAP)bmpTexture,0,iHeight,(void*)bits,bmi,DIB_RGB_COLORS);
		destDC.DeleteDC();
		free(bits);

		break;

//	default:
		return;
	}


	m_Canvas.SetBitmap((HBITMAP)bmpTexture);
	if (bmi) free(bmi);

	SetWindowPos(NULL,0,0,max(300,iWidth+30),iHeight+80,SWP_NOZORDER | SWP_NOMOVE);

}

int CEditorTexture::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	m_Border.Create(NULL,WS_VISIBLE | SS_GRAYRECT,CRect(0,40,100,100),this);
	m_Border.ModifyStyleEx(0,WS_EX_CLIENTEDGE);
	m_Canvas.Create(NULL,WS_VISIBLE | SS_BITMAP,CRect(2,42,100,100),this);

	return 0;
}



void CEditorTexture::OnSize(UINT nType, int cx, int cy)
{
	m_Border.SetWindowPos(NULL,0,0,cx,cy-40,SWP_NOZORDER | SWP_NOMOVE);
}


