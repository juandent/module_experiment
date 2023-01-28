// ControlsTest.cpp : implementation file
//

#include "pch.h"
#include "Client_MFCPP20_Modules.h"
#include "ControlsTest.h"

#include <sqlite_orm\sqlite_orm.h>

#include "Persistent_passwords.h"

// ControlsTest

IMPLEMENT_DYNCREATE(ControlsTest, CFormView)

ControlsTest::ControlsTest()
	: CFormView(IDD_ControlsTest),
	m_passwordLB{ db, m_password_listbox, [](const Password& password)
		{
			return util::to_cstring( password.simple_dump());
		} }
{

}

ControlsTest::~ControlsTest()
{
}

void ControlsTest::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_C_GRID2, m_grid);
	DDX_Control(pDX, IDC_E_ID, m_id);
	DDX_Control(pDX, IDC_L_LOCATIONS, m_password_listbox);
	DDX_Control(pDX, IDC_C_GRID_PASSWORDS, m_grid_passwords);
}

BEGIN_MESSAGE_MAP(ControlsTest, CFormView)
	ON_LBN_SELCHANGE(IDC_L_LOCATIONS, &ControlsTest::OnSelchangeLLocations)
	ON_NOTIFY(GVN_SELCHANGED, IDC_C_GRID2, OnGridStartSelChange)
END_MESSAGE_MAP()


// ControlsTest diagnostics

#ifdef _DEBUG
void ControlsTest::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void ControlsTest::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// ControlsTest message handlers

void ControlsTest::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();


	// CEdit edt;
	// auto opt = getCurrent<
	// export template<typename Database, typename Table>
	// 	std::optional<Table> getCurrent(CEdit & editCtrl, Database & db)

	// TODO: Add your specialized code here and/or call the base class
	m_id << 1;
	auto id = getCurrent<Password>(m_id, db);
	m_grid.Initialize(true);

	// initialize grid for all passwords
	auto lines = db.get_all<Password>();
	std::vector<std::string> headers{ "ID", "BEG DATE", "FK LOCATION", "PASSWORD"};

	m_password_displayer.reset(new GridDisplayer<Password>(m_grid_passwords, std::move(lines), std::move(headers)));

	m_password_displayer->display(&Password::id, &Password::begining_date, &Password::fkey_location, &Password::password);

	// initialize listbox
	auto passwords = db.get_all<Password>();
	m_passwordLB.loadLB(passwords);

}


void ControlsTest::OnSelchangeLLocations()
{
	// TODO: Add your control notification handler code here
	auto password = m_passwordLB.current();

}

void ControlsTest::OnGridStartSelChange(NMHDR* pNotifyStruct, LRESULT*)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*)pNotifyStruct;
	auto row = pItem->iRow;
	auto col = pItem->iColumn;

	if (row < 1) return;

	auto location_id = m_grid.GetIdFromRow(row);

}
