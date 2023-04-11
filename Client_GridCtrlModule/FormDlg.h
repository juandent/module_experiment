#pragma once
#include "afxdialogex.h"

import GridControl;

// FormDlg dialog

class FormDlg : public CDialog
{
	DECLARE_DYNAMIC(FormDlg)

public:
	FormDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~FormDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FormDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CGridCtrl m_grid;
	virtual BOOL OnInitDialog();
};
