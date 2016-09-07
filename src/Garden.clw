; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFF8Text
LastTemplate=generic CWnd
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Garden.h"
LastPage=0

ClassCount=9
Class1=CGardenApp
Class3=CMainFrame
Class4=CChildFrame

ResourceCount=11
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_GARDENTYPE
Class2=CChildView
Class5=CAboutDlg
Resource4=IDD_ABOUTBOX (English (U.S.))
Resource5=IDR_MAINFRAME (English (U.S.))
Resource6=IDR_INDEX_BAR (English (U.S.))
Class6=CIndexBar
Resource7=IDD_COMPILE (English (U.S.))
Resource8=IDR_GARDENTYPE (English (U.S.))
Class7=CProgressDlg
Resource9=IDR_EDITORTEXT_TOOLMENU (English (U.S.))
Class8=CCompileSelect
Class9=CFF8Text
Resource10=IDR_INDEX (English (U.S.))
Resource11=CG_IDD_PROGRESS

[CLS:CGardenApp]
Type=0
HeaderFile=Garden.h
ImplementationFile=Garden.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=IDC_FILES_MAIN

[CLS:CChildView]
Type=0
HeaderFile=ChildView.h
ImplementationFile=ChildView.cpp
Filter=N

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CMDIFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
BaseClass=CMDIChildWnd
VirtualFilter=mfWC
LastObject=CChildFrame


[CLS:CAboutDlg]
Type=0
HeaderFile=Garden.cpp
ImplementationFile=Garden.cpp
Filter=D
LastObject=CAboutDlg
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7
Command3=ID_FILE_MRU_FILE1

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
CommandCount=8
Command8=ID_APP_ABOUT

[MNU:IDR_GARDENTYPE]
Type=1
Class=CGardenView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_VIEW_TOOLBAR
Command13=ID_VIEW_STATUS_BAR
Command14=ID_WINDOW_NEW
CommandCount=18
Command6=ID_FILE_MRU_FILE1
Command7=ID_APP_EXIT
Command8=ID_EDIT_UNDO
Command15=ID_WINDOW_CASCADE
Command16=ID_WINDOW_TILE_HORZ
Command17=ID_WINDOW_ARRANGE
Command18=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
CommandCount=13
Command4=ID_EDIT_UNDO
Command13=ID_PREV_PANE


[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_OPENFILE
Command2=ID_SAVEFILE
Command3=ID_OPENPROJECT
Command4=ID_DECOMPILE
Command5=ID_COMPILE
CommandCount=5

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_OPENPROJECT
Command2=ID_DECOMPILE
Command3=ID_COMPILE
Command4=ID_APP_EXIT
Command5=ID_VIEW_TOOLBAR
Command6=ID_VIEW_STATUS_BAR
Command7=ID_APP_ABOUT
CommandCount=7

[MNU:IDR_GARDENTYPE (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_CLOSE
Command3=ID_APP_EXIT
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_VIEW_TOOLBAR
Command9=ID_VIEW_STATUS_BAR
Command10=ID_WINDOW_CASCADE
Command11=ID_WINDOW_TILE_HORZ
Command12=ID_WINDOW_ARRANGE
Command13=ID_APP_ABOUT
CommandCount=13

[MNU:IDR_INDEX_BAR (English (U.S.))]
Type=1
Class=?
CommandCount=0

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_COPY
Command2=ID_DECOMPILE
Command3=ID_FILE_NEW
Command4=ID_OPENPROJECT
Command5=ID_EDIT_PASTE
Command6=ID_EDIT_UNDO
Command7=ID_EDIT_CUT
Command8=ID_COMPILE
Command9=ID_NEXT_PANE
Command10=ID_PREV_PANE
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_EDIT_CUT
Command14=ID_EDIT_UNDO
CommandCount=14

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342308480
Control2=IDC_STATIC,static,1342308352
Control3=IDOK,button,1342373889
Control4=IDC_STATIC,static,1342181390
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[DLG:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
ControlCount=1
Control1=IDC_STATIC,static,1342308352

[CLS:CIndexBar]
Type=0
HeaderFile=IndexBar.h
ImplementationFile=IndexBar.cpp
BaseClass=CWnd
Filter=W
LastObject=CIndexBar
VirtualFilter=WC

[MNU:IDR_INDEX (English (U.S.))]
Type=1
Class=?
Command1=ID_ARCHIVE_OPEN
Command2=ID_ARCHIVE_OPENAS
Command3=ID_ARCHIVE_EXTRACT
Command4=ID_ARCHIVE_DELETE
Command5=ID_ARCHIVE_PROPERTIES
Command6=ID_ARCHIVE_SORTNONE
Command7=ID_ARCHIVE_SORTNAME
Command8=ID_ARCHIVE_SORTTYPE
Command9=ID_ARCHIVE_SORTSIZE
Command10=ID_ARCHIVE_SORTREV
Command11=ID_ARCHIVE_INSERT
Command12=ID_ARCHIVE_LGPPROP
CommandCount=12

[DLG:CG_IDD_PROGRESS]
Type=1
Class=CProgressDlg
ControlCount=5
Control1=CG_IDC_PROGDLG_PROGRESS,msctls_progress32,1350565888
Control2=CG_IDC_TITLE,static,1342308353
Control3=CG_IDC_CURRENTFILE,static,1342308353
Control4=CG_IDC_CURRENTFILE2,static,1342308353
Control5=CG_IDC_PROGDLG_TOTAL,msctls_progress32,1350565888

[CLS:CProgressDlg]
Type=0
HeaderFile=ProgDlg.h
ImplementationFile=ProgDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CG_IDC_CURRENTFILE

[DLG:IDD_COMPILE (English (U.S.))]
Type=1
Class=CCompileSelect
ControlCount=9
Control1=IDC_STATIC,static,1342308352
Control2=IDC_FILES_MAIN,listbox,1486963025
Control3=IDC_FILES_FIELD,listbox,1486963025
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287
Control6=IDC_COMPILE_SELECTED,button,1342177289
Control7=IDC_COMPILE_ALL,button,1342177289
Control8=IDCANCEL,button,1342373888
Control9=IDC_COMPILE,button,1342373889

[CLS:CCompileSelect]
Type=0
HeaderFile=CompileSelect.h
ImplementationFile=CompileSelect.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CCompileSelect

[CLS:CFF8Text]
Type=0
HeaderFile=editors.h
ImplementationFile=editortext.cpp
BaseClass=CWnd
Filter=W
LastObject=ID_ARCHIVE_EXTRACT
VirtualFilter=WC

[MNU:IDR_EDITORTEXT_TOOLMENU (English (U.S.))]
Type=1
Class=?
CommandCount=0

