// Sample.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "editcmd.h"
#include "Sample.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "SampleDoc.h"
#include "SampleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSampleApp

BEGIN_MESSAGE_MAP(CSampleApp, CWinApp)
	//{{AFX_MSG_MAP(CSampleApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_HELP_HELP, OnHelpHelp)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSampleApp construction

CSampleApp::CSampleApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSampleApp object

CSampleApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSampleApp initialization

BOOL CSampleApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// initialized OLE 2.0 libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDS_OLE_INIT_FAILED);
		return FALSE;
	}

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("RenderSoft TextCalc"));

	LoadStdProfileSettings(10);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_SAMPLETYPE,
		RUNTIME_CLASS(CSampleDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSampleView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
//	EnableShellOpen();
//	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	/*
	//if (cmdInfo!=NULL) 
		if (cmdInfo.m_strFileName!=NULL) 
			if (cmdInfo.m_strFileName!="") 
			*/

	if (cmdInfo.m_nShellCommand==CCommandLineInfo::FileOpen)
			m_nCmdShow=SW_SHOWMAXIMIZED;

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	//pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();


	if (IsFirstLoad()) {

		int rt=MessageBox(NULL,"This is the first time you are running TextCalc.\n\nDo you want to load the help file?", "Invoke Help?", MB_YESNO | MB_ICONQUESTION);
		
		CString px=GetProgPath();
		CString filex=px+"\\"+"progdata.nfo";
		
		FILE *fp;
		fp=fopen(filex,"w");
		if (fp!=NULL)  {
			fprintf(fp,"<Not first load> = true");
			if (fp!=NULL) fclose(fp);
		}

		if (rt==IDNO) return TRUE;

		POSITION x=GetFirstDocTemplatePosition( );
		if (x==NULL) return TRUE;
		
		CDocTemplate* tp=GetNextDocTemplate(x);
		CSampleDoc* doc=NULL;
		if (tp!=NULL) {
				
			POSITION z=tp->GetFirstDocPosition( ); 
			
			if (z!=NULL)
				doc=(CSampleDoc* ) tp->GetNextDoc(z);

		}

		CSampleView * dview=NULL;
		if (doc!=NULL) {
			
			POSITION y=doc->GetFirstViewPosition(); 
			if (y!=NULL)
				dview=(CSampleView *) doc->GetNextView(y); 
		
			if (dview!=NULL) {
				dview->insertFile("Help.txt",101);

				pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
				//pMainFrame->UpdateWindow();

			}

		}
		

	}

	return TRUE;
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
		// No message handlers
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
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CSampleApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSampleApp commands

void CSampleApp::OnHelpHelp() 
{
	// TODO: Add your command handler code here
	//OpenDocumentFile ("Help.txt");
	
	POSITION x=GetFirstDocTemplatePosition( );
	if (x==NULL) return;

	CDocTemplate* tp=GetNextDocTemplate(x);
	if (tp==NULL) return;

	CSampleDoc* doc=(CSampleDoc* ) tp->OpenDocumentFile(NULL);
	if (doc==NULL) return;

	POSITION y=doc->GetFirstViewPosition(); 
	if (y==NULL) return;

	CSampleView * dview=(CSampleView *) doc->GetNextView(y); 
	if (dview==NULL) return;

	dview->insertFile("Help.txt",101);

	CMainFrame* pMainFrame=(CMainFrame*) AfxGetMainWnd();
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	//pMainFrame->UpdateWindow();
	
	//OnFileNew();
	
}

BOOL CSampleApp::IsFirstLoad()
{
	CString px=GetProgPath();
	CString filex=px+"\\"+"progdata.nfo";
	FILE *fp;
	fp=fopen(filex,"r");
	if (fp!=NULL)  {
		fclose(fp);
		return FALSE;
	}
	else
		return TRUE;

}


CString CSampleApp::GetProgPath()
{

	TCHAR    szTemp[300];
	CFile converter;
	CString result;

	// get root
	GetModuleFileName( NULL, szTemp, 300 );

	CString path=(CString)szTemp;
	path=path.Left(path.ReverseFind('\\'));
	return path;
	

}
