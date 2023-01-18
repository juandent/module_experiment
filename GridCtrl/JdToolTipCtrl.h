#pragma once

#include "GridCtrl.h"

// CJdToolTipCtrl

class  CJdToolTipCtrl : public CToolTipCtrl
{
	DECLARE_DYNAMIC(CJdToolTipCtrl)

public:
	CJdToolTipCtrl();
	virtual ~CJdToolTipCtrl();

	BOOL AddWindowTool(CWnd* pWnd, LPCTSTR pszText);
	BOOL AddRectTool(CWnd* pWnd, LPCTSTR pszText, LPCRECT pRect, UINT nIDTool);

protected:
	DECLARE_MESSAGE_MAP()
};


