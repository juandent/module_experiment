
// Client_MFCPP20_Modules.h : main header file for the Client_MFCPP20_Modules application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CClientMFCPP20ModulesApp:
// See Client_MFCPP20_Modules.cpp for the implementation of this class
//

class CClientMFCPP20ModulesApp : public CWinAppEx
{
public:
	CClientMFCPP20ModulesApp() noexcept;


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
};

extern CClientMFCPP20ModulesApp theApp;
