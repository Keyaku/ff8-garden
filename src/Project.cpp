// Project.cpp: implementation of the CProject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Garden.h"
#include "Project.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProject::CProject()
{

}

CProject::~CProject()
{

}

//DEL int CProject::Create(LPCTSTR szFile)
//DEL {
//DEL 	src.Close();
//DEL 
//DEL 	if (!src.Open(szFile,CFile::modeWrite | CFile::modeCreate)) return 0;
//DEL 
//DEL 	return 1;
//DEL }

int CProject::AddFile(LPCTSTR szName, LPCTSTR szArchive, BOOL isarchive, BOOL compressed, UINT uSize)
{
	int j,c=0,last=-1;
	BOOL b = FALSE;

	for (int i=0;(UINT)i<strlen(szName);i++) {
		if (szName[i] == '\\') {
			if (nDirs == 0) {
				dirs[nDirs].parent = -1;
				dirs[nDirs].type = 0;
				memset(dirs[nDirs].szName,0,64);
				strncpy(dirs[nDirs].szName,szName+c,i-c);
				last = nDirs;
				nDirs++;
			} else {
				for (j=0;(UINT)j<nDirs;j++) {
//					TRACE("%s, %s, %u\n",dirs[j].szName,szName+c,i-c);
					if (!strnicmp(dirs[j].szName,szName+c,i-c) && (dirs[j].parent == (USHORT)last)) {
						b = TRUE;
						break;
					}

				}

				if (b) {
					last = j;
				} else {
					dirs[nDirs].parent = last;
					dirs[nDirs].type = 0;
					memset(dirs[nDirs].szName,0,64);
					strncpy(dirs[nDirs].szName,szName+c,i-c);
					last = nDirs;
					nDirs++;
				}

				b = FALSE;
			}
			c = i+1;
		}
	}
	
	strncpy(files[nFiles].szFilename,szName,64);

	if (isarchive) {
		files[nFiles].type = 2;
		for (i=0;(UINT)i<nArchives;i++) {
			if (!strnicmp(szArchive,datafiles[i].szName,16)) {
				files[nFiles].archive = i;
				goto archivefound;
			}
		}
	} else {
		for (i=0;(UINT)i<nArchives;i++) {
			if (!strnicmp(szArchive,datafiles[i].szName,16)) {
				files[nFiles].type = 0;
				files[nFiles].archive = i;
				goto archivefound;
			}
		}
		for (i=0;(UINT)i<nArchives2;i++) {
			if (!strnicmp(szArchive,archives[i].szName,64)) {
				files[nFiles].type = 1;
				files[nFiles].archive = i;
				goto archivefound;
			}
		}
	}
	
	return 0;

archivefound:
	files[nFiles].compressed = compressed;
	files[nFiles].uSize = uSize;

	nFiles++;

	return nFiles;
	
}

int CProject::AddArchive(LPCTSTR szName, BOOL datafile, int archive)
{
	if (datafile) {
		for (int i=0;(UINT)i<nArchives;i++)
			if (!strnicmp(datafiles[i].szName,szName,16)) return i;
		strncpy(datafiles[nArchives].szName,szName,16);
		return nArchives++;
	} else {
		for (int i=0;(UINT)i<nArchives2;i++)
			if (!strnicmp(archives[i].szName,szName,64)) return i;
		strncpy(archives[nArchives2].szName,szName,64);
		archives[nArchives2].archive = archive;
		return nArchives2++;
	}
	return -1;
}

void CProject::Save(LPCTSTR szFile)
{
	if (!src.Open(szFile,CFile::modeWrite | CFile::modeCreate)) return;

	UINT tag = 0x82050FF8;
	src.Write(&tag,4);

	src.Write(&nArchives,4);
	src.Write(&nArchives2,4);
	src.Write(&nFiles,4);
	src.Write(&nDirs,4);
	
	if (nArchives) src.Write(datafiles,sizeof(FF8DATAFILE)*nArchives);
	if (nArchives2) src.Write(archives,sizeof(GARDENARCHIVEENTRY)*nArchives2);
	if (nDirs) src.Write(dirs,sizeof(DIRECTORIES)*nDirs);
	if (nFiles) src.Write(files,sizeof(GARDENFILEENTRY)*nFiles);

	name = src.GetFileTitle();

	src.Close();

}

int CProject::Load(LPCTSTR szFile)
{
	if (!src.Open(szFile,CFile::modeRead)) return 0;

	UINT tag;
	src.Read(&tag,4);
	if (tag != 0x82050FF8) {
		src.Close();
		return 0;
	}

	src.Read(&nArchives,4);
	src.Read(&nArchives2,4);
	src.Read(&nFiles,4);
	src.Read(&nDirs,4);

	if (nArchives) src.Read(datafiles,sizeof(FF8DATAFILE)*nArchives);
	if (nArchives2) src.Read(archives,sizeof(GARDENARCHIVEENTRY)*nArchives2);
	if (nDirs) src.Read(dirs,sizeof(DIRECTORIES)*nDirs);
	if (nFiles) src.Read(files,sizeof(GARDENFILEENTRY)*nFiles);
	
	name = src.GetFileTitle();

	src.Close();

	return nFiles;

}

void CProject::ClearProject()
{
	nArchives = 0;
	nArchives2 = 0;
	nFiles = 0;
	nDirs = 0;
}

CString CProject::GetName()
{
	return CString(name);
}


CString CProject::GetFileName(int index)
{
	char buf[100];
	memset(buf,0,100);
	strncpy(buf,files[index].szFilename,64);
	return CString(buf);
}

UINT CProject::GetFileSize(int index)
{
	return files[index].uSize;
}

//DEL int CProject::GetDirCount()
//DEL {
//DEL 	return nDirs;
//DEL }

CString CProject::GetDirName(int index)
{
	char buf[100];
	memset(buf,0,100);
	strncpy(buf,dirs[index].szName,64);
	return CString(buf);
}

int CProject::GetDirParent(int index)
{
	return dirs[index].parent;
}
