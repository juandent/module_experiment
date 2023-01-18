// ControlsTest.cpp : implementation file
//

#include "pch.h"
#include "Client_MFCPP20_Modules.h"
#include "ControlsTest.h"


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
