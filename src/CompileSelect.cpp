// CompileSelect.cpp : implementation file
//

#include "stdafx.h"
#include "Garden.h"
#include "CompileSelect.h"
#include "Project.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCompileSelect dialog


CCompileSelect::CCompileSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CCompileSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCompileSelect)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCompileSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCompileSelect)
	DDX_Control(pDX, IDC_FILES_MAIN, m_Main);
	DDX_Control(pDX, IDC_FILES_FIELD, m_Field);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCompileSelect, CDialog)
	//{{AFX_MSG_MAP(CCompileSelect)
	ON_BN_CLICKED(IDC_COMPILE, OnCompile)
	ON_BN_CLICKED(IDC_COMPILE_ALL, OnCompileAll)
	ON_BN_CLICKED(IDC_COMPILE_SELECTED, OnCompileSelected)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCompileSelect message handlers

BOOL CCompileSelect::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	extern CProject theProject;

	CheckDlgButton(IDC_COMPILE_ALL,1);

	CString tmp, tmp2;
	for (int i=0;i<(int)theProject.nArchives2;i++) {
		tmp = theProject.archives[i].szName;
		tmp2 = (LPCTSTR)tmp + tmp.ReverseFind('\\') + 1;
		m_Field.AddString(" " + tmp2);
		m_Field.SetCheck(i,1);
	}
	for (i=0;i<(int)theProject.nArchives;i++) {
		tmp = theProject.datafiles[i].szName;
		m_Main.AddString(" " + tmp);
		m_Main.SetCheck(i,1);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCompileSelect::OnCompile() 
{
	// TODO: Add your control notification handler code here
	for (int i=0;i<m_Field.GetCount();i++) {
		fFlags[i] = m_Field.GetCheck(i);
	}
	for (i=0;i<m_Main.GetCount();i++) {
		fFlags[m_Field.GetCount()+i] = m_Main.GetCheck(i);
	}

	EndDialog(IDOK);
}

void CCompileSelect::OnCompileAll() 
{
	// TODO: Add your control notification handler code here
	m_Field.EnableWindow(FALSE);
	m_Main.EnableWindow(FALSE);

}

void CCompileSelect::OnCompileSelected() 
{
	// TODO: Add your control notification handler code here
	m_Field.EnableWindow(TRUE);
	m_Main.EnableWindow(TRUE);
	
}
