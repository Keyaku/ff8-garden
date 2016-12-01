// Garden.cpp : Defines the class behaviors for the application.
//

#include "ui_win32/StdAfx.h"
#include "Garden.h"

#include "ui_win32/MainFrm.h"
#include "ui_win32/ChildFrm.h"
#include "ProgDlg.h"

#include "archive.h"
#include "project.h"
#include "editors.h"

#include "IndexBar.h"
#include "CompileSelect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGardenApp

BEGIN_MESSAGE_MAP(CGardenApp, CWinApp)
	//{{AFX_MSG_MAP(CGardenApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_DECOMPILE, OnDecompile)
	ON_COMMAND(ID_OPENPROJECT, OnOpenproject)
	ON_COMMAND(ID_COMPILE, OnCompile)
	ON_COMMAND(ID_OPENFILE, OnOpenfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGardenApp construction

CGardenApp::CGardenApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGardenApp object

CGardenApp theApp;
CProject theProject;

/////////////////////////////////////////////////////////////////////////////
// CGardenApp initialization

BOOL CGardenApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));


	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.

	CMDIFrameWnd* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// create main MDI frame window
	if (!pFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;

	// try to load shared MDI menus and accelerator table
	//TODO: add additional member variables and load calls for
	//	additional menu types your application may need. 

	HINSTANCE hInst = AfxGetResourceHandle();
	m_hMDIMenu  = ::LoadMenu(hInst, MAKEINTRESOURCE(IDR_GARDENTYPE));
	m_hMDIAccel = ::LoadAccelerators(hInst, MAKEINTRESOURCE(IDR_GARDENTYPE));

	pFrame->m_bAutoMenuEnable = FALSE;

	// The main window has been initialized, so show and update it.
	pFrame->ShowWindow(m_nCmdShow);
	pFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGardenApp message handlers

int CGardenApp::ExitInstance() 
{
	//TODO: handle additional resources you may have added
	if (m_hMDIMenu != NULL)
		FreeResource(m_hMDIMenu);
	if (m_hMDIAccel != NULL)
		FreeResource(m_hMDIAccel);

	return CWinApp::ExitInstance();
}

void CGardenApp::OnFileNew() 
{

	CFile src,dest;
	src.Open("D:\\Final Fantasy VIII\\Data\\_field\\bgsecr_1\\bgsecr_1.msd",CFile::modeRead);
	dest.Open("D:\\Final Fantasy VIII\\Data\\_field\\bgsecr_1\\bgsecr_1.msd.cmp",CFile::modeReadWrite | CFile::modeCreate);

	CFF8Archive ff8;
	int r = ff8.DeflateFile(&dest,&src);

	TRACE("%u:%u - %02.1f%%\n",r,src.GetLength(),(float)r / (float)src.GetLength()*100.0);
	dest.SeekToBegin();
	src.Close();
	src.Open("D:\\Final Fantasy VIII\\Data\\_field\\bgsecr_1\\bgsecr_1.msd.exp",CFile::modeWrite | CFile::modeCreate);

	r = ff8.InflateFile(&src,&dest,0x1000);
	TRACE("%u\n",r);

}



/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CGardenApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CGardenApp message handlers


void CGardenApp::OnDecompile() 
{
	// Attempt to locate Final Fantasy VIII

	CString FF8Dir;

	HKEY keyReg;
	FF8Dir = ""; // Set the dir to nothing

	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE,"software",0,KEY_ALL_ACCESS,&keyReg))
	{
		HKEY keyReg2;
		if (ERROR_SUCCESS == RegOpenKeyEx(keyReg,"Square Soft, Inc",0,KEY_ALL_ACCESS,&keyReg2))
		{
			HKEY keyReg3;
			if (ERROR_SUCCESS == RegOpenKeyEx(keyReg2,"FINAL FANTASY VIII",0,KEY_ALL_ACCESS,&keyReg3))
			{
				HKEY keyReg4;
				if (ERROR_SUCCESS == RegOpenKeyEx(keyReg3,"1.00",0,KEY_ALL_ACCESS,&keyReg4))
				{
					char buf[MAX_PATH];
					unsigned long pulLen = (ULONG)MAX_PATH;

					unsigned long lType = REG_SZ;
					long lReturn = 0;

					lReturn = RegQueryValueEx(
						keyReg4,
						"AppPath",
						NULL,
						&lType,
						(UCHAR*)&buf,
						&pulLen );

					if (ERROR_SUCCESS == lReturn)
					{
						FF8Dir = buf;
						if (strlen(FF8Dir) != 0)
						{
							if (FF8Dir.GetAt(strlen(FF8Dir)-1) != 92) FF8Dir += "\\";
							FF8Dir += "Data\\";
						}
					}
					RegCloseKey(keyReg4);
				}
				RegCloseKey(keyReg3);
			}
			RegCloseKey(keyReg2);
		}
		RegCloseKey(keyReg);
	}

	if (strlen(FF8Dir) == 0) {
		char pFolder[MAX_PATH];
		BROWSEINFO bi;
		ITEMIDLIST * pItemIDList;
		memset(&bi, 0, sizeof(bi));
		bi.hwndOwner = AfxGetMainWnd()->GetSafeHwnd();
		bi.pszDisplayName = pFolder;
		bi.lpszTitle = "Please point to the directory where Final Fantasy VIII is installed.";
		bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_VALIDATE;

		if( (pItemIDList=SHBrowseForFolder(&bi)) != NULL )
		{
			SHGetPathFromIDList( pItemIDList, FF8Dir.GetBuffer(MAX_PATH) );
			if (FF8Dir.GetAt(strlen(FF8Dir)-1) != '\\') FF8Dir += "\\";
			FF8Dir += "Data\\";
		}
		else
			return;
	}

	// Select where to create project
	CFileDialog dlgFile(FALSE,
		"gpr",
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"Garden projects (*.gpr)|*.gpr|All files (*.*)|*.*||",
		AfxGetMainWnd());

	char namebuf[MAX_PATH];
	GetModuleFileName(NULL,namebuf,MAX_PATH);
	dlgFile.m_ofn.lpstrInitialDir = namebuf;

	if (IDCANCEL == dlgFile.DoModal()) return;

	strProjectFile = dlgFile.GetPathName();
	GetFileTitle(strProjectFile,strProjectPath.GetBuffer(MAX_PATH),MAX_PATH);
	int l = strlen(strProjectPath);
	memset(namebuf,0,MAX_PATH);
	strncpy(namebuf,strProjectFile,strlen(strProjectFile)-l);
	strProjectPath = namebuf;



	// For each .fs file, try decompressing

	CProgressDlg dlgProg;

	dlgProg.Create();

	CFileFind ff;
	CString buf = FF8Dir;
	buf += "*.fs";
	ff.FindFile(buf);
	if (!ff.FindNextFile()) {
		MessageBox(AfxGetMainWnd()->GetSafeHwnd(),"No data files found.","Garden",MB_ICONEXCLAMATION);
		return;
	}

	
	const CString strProjectPath2 = strProjectPath;

	BOOL bBreak = FALSE;
	int nfiles = 0;
	CString files[32];
	while (1) {
		files[nfiles++] = ff.GetFileTitle();
		if (bBreak) break;
		if (!ff.FindNextFile()) bBreak = TRUE;
	}

	// Extract all data files

	theProject.ClearProject();

	CFF8Archive ff8;
	char archivebuf[MAX_PATH];
	char dirbuf[MAX_PATH];
	int i,a;
	UINT n;
	for (int iFile = 0; iFile<nfiles; iFile++) {
		a = theProject.AddArchive(files[iFile],TRUE,0);
		strcpy(archivebuf,FF8Dir);
		strcat(archivebuf,files[iFile]);
		ff8.Load(archivebuf);
		dlgProg.SetTotalRange(0,ff8.GetCount());
		dlgProg.SetTotalPos(0);
		dlgProg.SetStatusFile(files[iFile]);
		for (i=0;i<ff8.GetCount();i++) {
			memset(dirbuf,0,MAX_PATH);
			strcpy(dirbuf,strProjectPath2);
			memset(namebuf,0,MAX_PATH);
			strcat(dirbuf,ff8.GetFileName(namebuf,i)+3);

			GetFileTitle(dirbuf,namebuf,MAX_PATH);
			dlgProg.SetStatus(namebuf);
			n = ff8.ExtractFile(i,dirbuf,&dlgProg);
			if (!strnicmp(namebuf+(strlen(namebuf)-3),".fi",3) ||
				!strnicmp(namebuf+(strlen(namebuf)-3),".fl",3) ||
				!strnicmp(namebuf+(strlen(namebuf)-3),".fs",3)) {
				CFF8Archive ff82;
				int n2;
				char archivebuf2[MAX_PATH];
				char namebuf2[MAX_PATH];
				memset(namebuf,0,MAX_PATH);
				strncpy(namebuf,dirbuf,strlen(dirbuf)-3);
				if (ff82.Load(namebuf)) {
					int w=0;
					memset(archivebuf2,0,MAX_PATH);
					strncpy(archivebuf2,namebuf+strlen(strProjectPath2),strlen(namebuf)-strlen(strProjectPath2));
					theProject.AddArchive(archivebuf2,FALSE,a);

					for (int j=0;j<ff82.GetCount();j++) {
						memset(dirbuf,0,MAX_PATH);
						strcpy(dirbuf,strProjectPath2);
						memset(namebuf2,0,MAX_PATH);
						strcat(dirbuf,ff82.GetFileName(namebuf2,j)+3);
						n2 = ff82.ExtractFile(j,dirbuf,NULL);
						theProject.AddFile(namebuf2+3,archivebuf2,FALSE,ff82.IsCompressed(j),n2);
					}
				}
				theProject.AddFile(ff8.GetFileName(namebuf,i)+3,ff.GetFileTitle(), TRUE, ff8.IsCompressed(i),n);
			} else {
				theProject.AddFile(ff8.GetFileName(namebuf,i)+3,ff.GetFileTitle(), FALSE, ff8.IsCompressed(i),n);
			}
			
			
			dlgProg.SetTotalPos(i);
#ifdef _DEBUG
			if (stricmp(files[iFile],"field"))
				break;
#endif
		}
	}

	strProjectPath = strProjectPath2;

	theProject.Save(strProjectFile);

	dlgProg.DestroyWindow();

	extern CIndexBar theIndex;

	theIndex.Update();

}

void CGardenApp::OnOpenproject() 
{
	// TODO: Add your command handler code here
	CFileDialog dlgFile(TRUE,
		"gpr",
		strProjectFile,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		"Garden projects (*.gpr)|*.gpr|All files (*.*)|*.*||",
		AfxGetMainWnd());

	char namebuf[MAX_PATH];
	GetModuleFileName(NULL,namebuf,MAX_PATH);
	dlgFile.m_ofn.lpstrInitialDir = namebuf;

	if (IDCANCEL == dlgFile.DoModal()) return;

	strProjectFile = dlgFile.GetPathName();
	GetFileTitle(strProjectFile,namebuf,MAX_PATH);
	strProjectPath = namebuf;
	int l = strlen(strProjectPath);
	memset(namebuf,0,MAX_PATH);
	strncpy(namebuf,strProjectFile,strlen(strProjectFile)-l);
	strProjectPath = namebuf;

	theProject.Load(strProjectFile);

	extern CIndexBar theIndex;
	theIndex.Update();
	
}



void CGardenApp::OnCompile() 
{
	// TODO: Add your command handler code here
	if (IDCANCEL == MessageBox(AfxGetMainWnd()->GetSafeHwnd(),
		"Before you proceed, it is wise to make backups of your existing\n"
		"data files. These are located in the 'data' folder under FF8 and\n"
		"have the suffices '.fi', '.fl' and '.fs'.\n\n"
		"Click OK to proceed.","Garden",MB_OKCANCEL | MB_ICONINFORMATION))
		return;


	BOOL *compile = new int[theProject.nArchives + theProject.nArchives2];

	CCompileSelect cs;
	cs.fFlags = compile;
	if (IDCANCEL == cs.DoModal()) {
		delete[] compile;
		return;
	}


	CString FF8Dir;

	HKEY keyReg;
	FF8Dir = ""; // Set the dir to nothing

	if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE,"software",0,KEY_ALL_ACCESS,&keyReg))
	{
		HKEY keyReg2;
		if (ERROR_SUCCESS == RegOpenKeyEx(keyReg,"Square Soft, Inc",0,KEY_ALL_ACCESS,&keyReg2))
		{
			HKEY keyReg3;
			if (ERROR_SUCCESS == RegOpenKeyEx(keyReg2,"FINAL FANTASY VIII",0,KEY_ALL_ACCESS,&keyReg3))
			{
				HKEY keyReg4;
				if (ERROR_SUCCESS == RegOpenKeyEx(keyReg3,"1.00",0,KEY_ALL_ACCESS,&keyReg4))
				{
					char buf[MAX_PATH];
					unsigned long pulLen = (ULONG)MAX_PATH;

					unsigned long lType = REG_SZ;
					long lReturn = 0;

					lReturn = RegQueryValueEx(
						keyReg4,
						"AppPath",
						NULL,
						&lType,
						(UCHAR*)&buf,
						&pulLen );

					if (ERROR_SUCCESS == lReturn)
					{
						FF8Dir = buf;
						if (strlen(FF8Dir) != 0)
						{
							if (FF8Dir.GetAt(strlen(FF8Dir)-1) != 92) FF8Dir += "\\";
							FF8Dir += "Data\\";
						}
					}
					RegCloseKey(keyReg4);
				}
				RegCloseKey(keyReg3);
			}
			RegCloseKey(keyReg2);
		}
		RegCloseKey(keyReg);
	}

	if (strlen(FF8Dir) == 0) {
		char pFolder[MAX_PATH];
		BROWSEINFO bi;
		ITEMIDLIST * pItemIDList;
		memset(&bi, 0, sizeof(bi));
		bi.hwndOwner = AfxGetMainWnd()->GetSafeHwnd();
		bi.pszDisplayName = pFolder;
		bi.lpszTitle = "Please point to the directory where Final Fantasy VIII is installed.";
		bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_VALIDATE;

		if( (pItemIDList=SHBrowseForFolder(&bi)) != NULL )
		{
			SHGetPathFromIDList( pItemIDList, FF8Dir.GetBuffer(MAX_PATH) );
			if (FF8Dir.GetAt(strlen(FF8Dir)-1) != '\\') FF8Dir += "\\";
			FF8Dir += "Data\\";
		}
		else {
			delete[] compile;
			return;
		}
	}

	CProgressDlg dlgProg;
	dlgProg.Create();
	dlgProg.SetTitle("Compiling data files...");
	dlgProg.SetStatusFile("Field data");
	dlgProg.SetTotalRange(0,theProject.nArchives+theProject.nArchives2);
	CString strDir;
	CFile ar;
	CFF8Archive ff8;
	CString name;
	UINT i,j,k;
	for (i=0;i<theProject.nArchives2;i++) {
//		if (stricmp(theProject.archives[i].szName,"ff8\\Data\\eng\\FIELD\\mapdata\\bg\\bgsecr_2")) continue;
		if (!compile[i]) continue;
		dlgProg.SetStatus(theProject.archives[i].szName);
		dlgProg.SetTotalPos(i);
		dlgProg.SetPos(0);
		name = strProjectPath;
		name += theProject.archives[i].szName;
		ff8.Clear();
		ff8.SetFileName(name);
		k = 0;
		for (j=0;j<theProject.nFiles;j++)
			if (theProject.files[j].archive == i && theProject.files[j].type == 1) k++;
		ff8.SetFileCount(k);
		for (j=0;j<theProject.nFiles;j++) {
			if (theProject.files[j].archive == i && theProject.files[j].type == 1) {
				ff8.AddFile(strProjectPath + theProject.files[j].szFilename, CString("C:\\") + CString(theProject.files[j].szFilename),theProject.files[j].compressed);
//				dlgProg.SetPos(ff8.GetCount());
			}
		}
		ff8.Save(strProjectPath,&dlgProg);
	}

	dlgProg.SetStatusFile("Primary data files");

	for (i=0;i<theProject.nArchives;i++) {
//		if (stricmp(theProject.datafiles[i].szName,"field")) continue;
		if (!compile[theProject.nArchives2 + i]) continue;
		dlgProg.SetStatus(theProject.datafiles[i].szName);
		dlgProg.SetTotalPos(theProject.nArchives2 + i);
		dlgProg.SetPos(0);
		name = FF8Dir;
		name += theProject.datafiles[i].szName;
		ff8.Clear();
		ff8.SetFileName(name);
		k = 0;
		for (j=0;j<theProject.nFiles;j++)
			if (theProject.files[j].archive == i && theProject.files[j].type != 1) k++;
		ff8.SetFileCount(k);
		for (j=0;j<theProject.nFiles;j++) {
			if (theProject.files[j].archive == i && theProject.files[j].type != 1) {
				ff8.AddFile(strProjectPath + theProject.files[j].szFilename, CString("C:\\") + CString(theProject.files[j].szFilename),theProject.files[j].compressed);
//				dlgProg.SetPos(ff8.GetCount());
			}
		}
		ff8.Save(strProjectPath,&dlgProg);
	}

	delete[] compile;

}

void CGardenApp::OnOpenfile() 
{
	// TODO: Add your command handler code here
	if (GetKeyState(VK_SHIFT)&0x80) {
		return;
	}
	
	
	extern CIndexBar theIndex;
	CListCtrl *list = theIndex.GetList();
	int c = list->GetSelectionMark();
	DWORD d = list->GetItemData(c);

	char szFile[MAX_PATH];
	strcpy(szFile,strProjectPath);
	strcat(szFile,theProject.files[d].szFilename);

	CRuntimeClass *editor;

	CString dir2 = szFile;
	int o;
	o = dir2.ReverseFind('.');
	LPCTSTR suffix = (LPCTSTR)dir2+o;
	
	     if (!strnicmp(".msd",suffix,4)) editor = RUNTIME_CLASS(CEditorText);
	else if (!strnicmp(".tex",suffix,4)) editor = RUNTIME_CLASS(CEditorTexture);
	else if (!strnicmp(".lzs",suffix,4)) editor = RUNTIME_CLASS(CEditorTexture);
	else if (!strnicmp(".tim",suffix,4)) editor = RUNTIME_CLASS(CEditorTexture);
	else return;


	CMainFrame* pFrame = STATIC_DOWNCAST(CMainFrame, m_pMainWnd);

	// create a new MDI child window
	CChildFrame *child = (CChildFrame*)pFrame->CreateNewChild(
		editor, IDR_GARDENTYPE, m_hMDIMenu, m_hMDIAccel);

	child->LoadFile(szFile);

}
