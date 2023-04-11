// FormDialog.cpp : implementation file
//

#include "pch.h"
#include "Client_GridCtrlModule.h"
#include "afxdialogex.h"
#include "FormDialog.h"


// FormDialog dialog

IMPLEMENT_DYNAMIC(FormDialog, CDialogEx)

FormDialog::FormDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FORMVIEW, pParent)
{

}

FormDialog::~FormDialog()
{
}

void FormDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_CUSTOM1, m_grid);
}


BEGIN_MESSAGE_MAP(FormDialog, CDialogEx)
	ON_COMMAND(ID_FILE_OPENDIALOG, &FormDialog::OnFileOpendialog)
END_MESSAGE_MAP()


// FormDialog message handlers


void FormDialog::OnFileOpendialog()
{
	// TODO: Add your command handler code here
}
