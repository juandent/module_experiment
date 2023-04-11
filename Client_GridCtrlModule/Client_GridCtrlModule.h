
// Client_GridCtrlModule.h : main header file for the Client_GridCtrlModule application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CClientGridCtrlModuleApp:
// See Client_GridCtrlModule.cpp for the implementation of this class
//

class CClientGridCtrlModuleApp : public CWinAppEx
{
public:
	CClientGridCtrlModuleApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
		afx_msg void OnFileOpendialog();
};

extern CClientGridCtrlModuleApp theApp;
