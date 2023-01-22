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
	: CFormView(IDD_ControlsTest)
{

}

ControlsTest::~ControlsTest()
{
}

void ControlsTest::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_C_GRID, m_grid);
	DDX_Control(pDX, IDC_E_ID, m_id);
}

BEGIN_MESSAGE_MAP(ControlsTest, CFormView)
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
}
