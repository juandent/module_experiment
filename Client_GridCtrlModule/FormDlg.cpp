// FormDlg.cpp : implementation file
//

#include "pch.h"
#include "Client_GridCtrlModule.h"
#include "afxdialogex.h"
#include "FormDlg.h"


// FormDlg dialog

IMPLEMENT_DYNAMIC(FormDlg, CDialog)

FormDlg::FormDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_FormDlg, pParent)
{

}

FormDlg::~FormDlg()
{
}

void FormDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID, m_grid);
}


BEGIN_MESSAGE_MAP(FormDlg, CDialog)
END_MESSAGE_MAP()


// FormDlg message handlers


BOOL FormDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_grid.SetRowCount(10);
	m_grid.SetColumnCount(5);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
