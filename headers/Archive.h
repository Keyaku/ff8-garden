// Archive.h: interface for the CArchive class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ARCHIVE_H__C90D2921_C1E9_11D3_815D_AF6BF6E47A3B__INCLUDED_)
#define AFX_ARCHIVE_H__C90D2921_C1E9_11D3_815D_AF6BF6E47A3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ProgDlg.h"





class CFF8Archive  
{
public:
	int Clear();
	int SetFileName (LPCTSTR szName);
	int SetFileCount (int files);
	int DeflateFile (CFile *dest, CFile *src);
	BOOL IsCompressed (int index);
	int CreateDir (LPCTSTR dir);
	LPSTR GetFileName (LPSTR buf, int index);
	int InflateFile (CFile *dest, CFile *src, DWORD dwSize);
	int ExtractFile (int index, LPCTSTR szFilename, CProgressDlg *dlg);
	int Save (CString strRelDir, CProgressDlg *dlg);
	int GetCount ();
	int Load (LPCTSTR szArchive);
	int AddFile(CString strFilename, CString strTag, BOOL compress);
	CFF8Archive();
	virtual ~CFF8Archive();


protected:
	CString strArchive;
	CFile fi, fl, fs;

	int nFiles;
	int nFilled;

	struct FF8FILEHEADER {
		char szName[64];		// Name stored in archive
		UINT uSize;				// Original file size
		UINT uOffset;			// Offset in archive
		BOOL bCompressed;		// File is compressed in archive
		UINT uCompressedSize;	// Compressed size. Only used when saving archives
	} *headers;

};

#endif // !defined(AFX_ARCHIVE_H__C90D2921_C1E9_11D3_815D_AF6BF6E47A3B__INCLUDED_)
