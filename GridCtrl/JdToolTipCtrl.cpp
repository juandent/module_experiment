// JdToolTipCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "JdToolTipCtrl.h"


// CJdToolTipCtrl

IMPLEMENT_DYNAMIC(CJdToolTipCtrl, CToolTipCtrl)

CJdToolTipCtrl::CJdToolTipCtrl()
{

}

CJdToolTipCtrl::~CJdToolTipCtrl()
{
}

BOOL CJdToolTipCtrl::AddWindowTool(CWnd * pWnd, LPCTSTR pszText)
{
	TOOLINFO ti;
	ti.cbSize = sizeof(TOOLINFO);
	ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
	ti.hwnd = pWnd->GetParent()->GetSafeHwnd();
	ti.uId = reinterpret_cast<UINT_PTR>(pWnd->GetSafeHwnd());
	ti.hinst = AfxGetInstanceHandle();
	ti.lpszText = (LPTSTR) pszText;

	return SendMessage(TTM_ADDTOOL, 0, reinterpret_cast<LPARAM>(&ti)) != 0;
}

BOOL CJdToolTipCtrl::AddRectTool(CWnd * pWnd, LPCTSTR pszText, LPCRECT pRect, UINT nIDTool)
{
	TOOLINFO ti;
	ti.cbSize = sizeof(TOOLINFO);
	ti.uFlags = TTF_SUBCLASS;
	ti.hwnd = pWnd->GetSafeHwnd();
	ti.uId = nIDTool;
	ti.hinst = AfxGetInstanceHandle();
	ti.lpszText = (LPTSTR)pszText;
	::CopyRect(&ti.rect, pRect);

	return SendMessage(TTM_ADDTOOL, 0, reinterpret_cast<LPARAM>(&ti)) != 0;
}


BEGIN_MESSAGE_MAP(CJdToolTipCtrl, CToolTipCtrl)
END_MESSAGE_MAP()



// CJdToolTipCtrl message handlers


