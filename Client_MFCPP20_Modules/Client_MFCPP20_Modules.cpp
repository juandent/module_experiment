
// Client_MFCPP20_Modules.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Client_MFCPP20_Modules.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "Client_MFCPP20_ModulesDoc.h"
#include "Client_MFCPP20_ModulesView.h"

#include "ControlsTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "Persistent_passwords.h"


#if 0
void use()
{
	using namespace sqlite_orm;


	using database_t = decltype(database());

	database().sync_schema();
	Location loc{ -1, "cpp_reference", "cpp_reference.com", "daniel@cpp_reference.com" };
	database().insert(loc);

	Password pwd{ -1, "jxql78", today(), 1 };
	database().insert(pwd);
	
	Money mny;

#if 0
	// using namespace control_contents;
	auto post = control_contents::Posting::get();
	post.WindowProc(10, 2000, 4000);
	CListBox box;

	control_contents::BoxContents<database_t, Password, &Password::id>(db, box, [](const Password& pw)
	{
			return util::to_cstring(pw.simple_dump());
	});
#endif

	auto lines = db.select(columns(&Location::id, &Password::id), cross_join<Password>());

	auto linesAsterisks = db.select(asterisk<Location>(), cross_join<Password>());

	//auto linesAsterisksTwo = db.select(columns(asterisk<Location>(), &Password::id), cross_join<Password>());

	auto linesAsterisksTwo = db.select(columns(&Location::id, &Password::id), cross_join<Password>());
}
#endif


// CClientMFCPP20ModulesApp

BEGIN_MESSAGE_MAP(CClientMFCPP20ModulesApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CClientMFCPP20ModulesApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CClientMFCPP20ModulesApp construction

CClientMFCPP20ModulesApp::CClientMFCPP20ModulesApp() noexcept
{
	m_bHiColorIcons = TRUE;


	m_nAppLook = 0;
	// support Restart Manager
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// If the application is built using Common Language Runtime support (/clr):
	//     1) This additional setting is needed for Restart Manager support to work properly.
	//     2) In your project, you must add a reference to System.Windows.Forms in order to build.
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ClientMFCPP20Modules.AppID.NoVersion"));

	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CClientMFCPP20ModulesApp object

CClientMFCPP20ModulesApp theApp;


// CClientMFCPP20ModulesApp initialization

BOOL CClientMFCPP20ModulesApp::InitInstance()
{
	//use();
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// AfxInitRichEdit2() is required to use RichEdit control
	// AfxInitRichEdit2();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)


	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_ClientMFCPP20ModulesTYPE,
		RUNTIME_CLASS(CClientMFCPP20ModulesDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(ControlsTest));
		// RUNTIME_CLASS(CClientMFCPP20ModulesView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// Dispatch commands specified on the command line.  Will return FALSE if
	// app was launched with /RegServer, /Register, /Unregserver or /Unregister.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	// The main window has been initialized, so show and update it
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CClientMFCPP20ModulesApp::ExitInstance()
{
	//TODO: handle additional resources you may have added
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CClientMFCPP20ModulesApp message handlers


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg() noexcept;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() noexcept : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// App command to run the dialog
void CClientMFCPP20ModulesApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CClientMFCPP20ModulesApp customization load/save methods

void CClientMFCPP20ModulesApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CClientMFCPP20ModulesApp::LoadCustomState()
{
}

void CClientMFCPP20ModulesApp::SaveCustomState()
{
}

// CClientMFCPP20ModulesApp message handlers



