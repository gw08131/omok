
// omok.cpp : Defines the class behaviors for the application.
//

#include "pch.h"
#include "framework.h"
#include "omok.h"
#include "omokDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ComokApp

BEGIN_MESSAGE_MAP(ComokApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// ComokApp construction

ComokApp::ComokApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only ComokApp object

ComokApp theApp;


// ComokApp initialization

BOOL ComokApp::InitInstance()
{
	CWinApp::InitInstance();

	ComokDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	
	return FALSE;
}

