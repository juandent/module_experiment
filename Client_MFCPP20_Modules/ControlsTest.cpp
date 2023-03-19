// ControlsTest.cpp : implementation file
//

#include "pch.h"
#include <chrono>
#include "Client_MFCPP20_Modules.h"
#include "ControlsTest.h"

#include <sqlite_orm\sqlite_orm.h>

#include "Persistent_passwords.h"


IMPLEMENT_DYNCREATE(ControlsTest, CFormView)

ControlsTest::ControlsTest()
	: CFormView(IDD_ControlsTest),
	m_passwordLB{ db, m_password_listbox, [](const Password& password)
		{
			return util::to_cstring( password.simple_dump());
		} },
	m_group_one_two{ {&m_one, &m_two}, {1,2} }
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
	DDX_Control(pDX, IDC_L_PASSWORDS, m_password_listbox);
	DDX_Control(pDX, IDC_C_GRID_PASSWORDS, m_grid_passwords);
	DDX_Control(pDX, IDC_G_GRID, m_grid_simple);
	DDX_Control(pDX, IDC_CHECK1, m_check1);
	DDX_Control(pDX, IDC_RADIO1, m_one);
	DDX_Control(pDX, IDC_RADIO2, m_two);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_date_time);
}

BEGIN_MESSAGE_MAP(ControlsTest, CFormView)
	ON_LBN_SELCHANGE(IDC_L_PASSWORDS, &ControlsTest::OnSelchangePasswords)
	ON_NOTIFY(GVN_SELCHANGED, IDC_C_GRID2, OnGridStartSelChange)
	ON_BN_CLICKED(IDC_CHECK1, &ControlsTest::OnClickedCheck1)
	ON_BN_CLICKED(IDC_RADIO1, &ControlsTest::OnClickedRadio)
	ON_BN_CLICKED(IDC_RADIO2, &ControlsTest::OnClickedRadio)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &ControlsTest::OnDatetimechangeDatetimepicker1)
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


	auto str = util::to_cstring(true);

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
	m_passwordLB.select_by_pk(passwords[0].id);

}


void ControlsTest::OnSelchangePasswords()
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


void ControlsTest::OnClickedCheck1()
{
	// TODO: Add your control notification handler code here
	// INSTEAD OF
	auto val = m_check1.GetCheck();
	// USE THIS
	bool is_checked;
	m_check1 >> is_checked;

}


void ControlsTest::OnClickedRadio()
{
	// TODO: Add your control notification handler code here
	int val;
	m_group_one_two >> val;

	m_check1 << (val != 1);
}


void ControlsTest::OnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	//pDTChange->st.wYear;
	std::chrono::sys_days date;
	m_date_time >> date;
	std::chrono::year_month_day ymd = date;

	*pResult = 0;
}


LRESULT ControlsTest::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if( Posting::get().WindowProc(message, wParam, lParam) == Posting::WindowProcNotHandled)
		return CFormView::WindowProc(message, wParam, lParam);
	return 0;
}
