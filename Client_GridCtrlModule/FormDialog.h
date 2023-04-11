#pragma once
#include "afxdialogex.h"

//import GridControl;

// FormDialog dialog

class FormDialog : public CDialogEx
{
	DECLARE_DYNAMIC(FormDialog)

public:
	FormDialog(CWnd* pParent = nullptr);   // standard constructor
	virtual ~FormDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FORMVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpendialog();
	//CJDGridCtrl m_grid;
};
