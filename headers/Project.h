// Project.h: interface for the CProject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROJECT_H__57CBEA81_C220_11D3_815D_C7C8B9F5213B__INCLUDED_)
#define AFX_PROJECT_H__57CBEA81_C220_11D3_815D_C7C8B9F5213B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CProject  
{
public:
	int GetDirParent (int index);
	CString GetDirName(int index);
	UINT GetFileSize (int index);
	CString GetFileName (int index);
	CString GetName();
	void ClearProject();
	int Load (LPCTSTR szFile);
	void Save (LPCTSTR szFile);
	int AddArchive (LPCTSTR szName, BOOL datafile = TRUE, int archive = 0);
	int AddFile (LPCTSTR szName, LPCTSTR szArchive, BOOL isarchive, BOOL compressed, UINT uSize);
	CProject();
	virtual ~CProject();




//protected:
	CString name;
	CFile src;

	// File layout:
	// - ID tag
	// - Size markers
	// - Original archives
	// - Archives2 (processed in reverse order)
	// 
	UINT nArchives;					// Number of archives
	UINT nArchives2;				// Number of archives2
	UINT nFiles;					// Total number of files
	UINT nDirs;						// Number of directories


	// Game data files
	struct FF8DATAFILE {
		char szName[16];
	} datafiles[16];

	struct GARDENARCHIVEENTRY {
		char szName[64];			// Name of archive (relative to project)
		UINT archive;				// Which data file does the archive belong to?
	} archives[2048];

	struct DIRECTORIES {
		char szName[64];			// Directory name
		USHORT type;				// 0: Directory   1: Archive   3: Project
		USHORT parent;				// Parent
	} dirs[2048];

	// Extracted files
	struct GARDENFILEENTRY {
		char szFilename[64];		// File name (relative to project)
		UINT uSize;					// Size of file
		BOOL compressed;			// 1 if file should be compressed, otherwise 0
		USHORT type;				// 0: Normal file   1: Part of a custom archive   2: The file _is_ an archive
		USHORT archive;				// Parent data file.
	} files[0x10000];


};

#endif // !defined(AFX_PROJECT_H__57CBEA81_C220_11D3_815D_C7C8B9F5213B__INCLUDED_)
