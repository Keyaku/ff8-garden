// ProgDlg.h : header file
// CG: This file was added by the Progress Dialog component

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog

#ifndef __PROGDLG_H__
#define __PROGDLG_H__

class CProgressDlg : public CDialog
{
// Construction / Destruction
public:
	void SetTitle (LPCTSTR szText);
	int SetTotalPos (int nPos);
	void SetTotalRange (int nLower, int nUpper);
	void SetStatusFile (LPCTSTR file);
	void SetStatus (LPCTSTR text);
    CProgressDlg(UINT nCaptionID = 0);   // standard constructor
    ~CProgressDlg();

    BOOL Create(CWnd *pParent=NULL);

    // Progress Dialog manipulation
    void SetRange(int nLower,int nUpper);
    int  SetPos(int nPos);
        
// Dialog Data
    //{{AFX_DATA(CProgressDlg)
	enum { IDD = CG_IDD_PROGRESS };
	CStatic	m_Title;
	CProgressCtrl	m_ProgressTotal;
	CStatic	m_Currentfile2;
	CStatic	m_Currentfile;
    CProgressCtrl	m_Progress;
	//}}AFX_DATA

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CProgressDlg)
    public:
    virtual BOOL DestroyWindow();
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:
	UINT m_nCaptionID;
    int m_nLower;
    int m_nUpper;
    int m_nStep;
    BOOL m_bParentDisabled;

    void ReEnableParent();

    virtual void OnCancel();
    virtual void OnOK() {}; 
    void PumpMessages();

    // Generated message map functions
    //{{AFX_MSG(CProgressDlg)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif // __PROGDLG_H__
