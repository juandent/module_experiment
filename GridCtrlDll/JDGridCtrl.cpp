// JDGridCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "JDGridCtrl.h"
#include <locale>
#include <cassert>

// CJDGridCtrl

IMPLEMENT_DYNAMIC(CJDGridCtrl, CGridCtrl)

CJDGridCtrl::CJDGridCtrl(int nRows, int nCols, int nFixedRows, int nFixedCols)
	: CGridCtrl(nRows, nCols, nFixedRows, nFixedCols)
{

}

CJDGridCtrl::~CJDGridCtrl()
{
}

void CJDGridCtrl::OnMouseLeave()
{
	m_tracking = FALSE;
	m_Tip.SendMessage(TTM_TRACKACTIVATE, (WPARAM)FALSE, (LPARAM)&m_ti);
}

void CJDGridCtrl::ScrollDownNRows(int num_rows)
{
	for(int row=0; row < num_rows; ++row)
	{
		SendMessage(WM_VSCROLL, SB_LINEDOWN, 0);
	}
}

void CJDGridCtrl::ScrollUpNRows(int num_rows)
{
	for (int row = 0; row < num_rows; ++row)
	{
		SendMessage(WM_VSCROLL, SB_LINEUP, 0);
	}
}

int CJDGridCtrl::RowNumberForFirstGridLine()
{
	for (int row = 1; row < GetRowCount(); ++row)
	{
		POINT point;
		bool isVisible = GetCellOrigin(row, 0, &point);
		if (isVisible)
		{
			return row;
		}
	}
	assert(false);
	return -1;
}

void CJDGridCtrl::Scroll(int row_to_select)
{
	const int first_row = RowNumberForFirstGridLine();

	if (row_to_select == first_row)	return;

	if (row_to_select > first_row)
	{
		ScrollDownNRows(row_to_select - first_row);
	}
	else
	{
		ScrollUpNRows(first_row - row_to_select);
	}
}
void CJDGridCtrl::SelectRow(int row_to_select)
{
	const auto column_count = GetColumnCount();
	SetSelectedRange(row_to_select, 0, row_to_select, column_count - 1);
}

void CJDGridCtrl::SetSelectAndScroll(int row_to_select)
{
	SelectRow(row_to_select);
	Scroll(row_to_select);
}

int CJDGridCtrl::GetSelectedMinRow() const
{
	if (GetSelectedCount())
	{
		auto cell_range = GetSelectedCellRange();

		auto row = cell_range.GetMinRow();
		return row;
	}
	return -1;
}


namespace
{
	constexpr static size_t MAX_BUFFER_FOR_TOOLTIP = 120;
}

namespace  JD
{
	// convert string to wstring
	inline std::wstring to_wstring(const std::string& str, const std::locale& loc = std::locale{})
	{
		std::vector<wchar_t> buf(str.size());
		std::use_facet<std::ctype<wchar_t>>(loc).widen(str.data(), str.data() + str.size(), buf.data());

		return std::wstring(buf.data(), buf.size());
	}

	// convert CString to string
	// inline std::string()

}

#if 0
int CJDGridCtrl::GetID(int row) const
{
	auto id_cs = GetItemText(row, m_id_column);
	auto location_id_s = Util::to_string(location_id_cs.GetBuffer());

	if (location_id_s.empty())	return -1;

	int location_id = std::stoi(location_id_s);
	return location_id;

}
#endif

void CJDGridCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	static CPoint oldPoint;

	if (!m_tracking)
	{
		TRACKMOUSEEVENT tme = { sizeof(TRACKMOUSEEVENT) };
		m_tracking = TRUE;
		tme.hwndTrack = GetSafeHwnd();
		tme.dwFlags = TME_LEAVE;

		TrackMouseEvent(&tme);
	}

	m_Tip.SendMessage(TTM_TRACKACTIVATE, (WPARAM)TRUE, (LPARAM)&m_ti);

	if (oldPoint != point)
	{
		oldPoint = point;

		CPoint ptScreen = point;

		ClientToScreen(&ptScreen);

		CCellID id = GetCellFromPt(point);

		bool bOutside = id.col == -1 || id.row == -1;


		if ( !bOutside)
		{
			auto cell = GetCell(id.row, id.col);
#if USING_CSTRING
			LPCTSTR str = { reinterpret_cast<LPCTSTR>(cell->GetData()) };
			if (str )
			{
				//TRACE(L"%ls\n", str);
				m_ti.lpszText = const_cast<LPTSTR>(str); //  L"Hola Grid!";              //     GetItemDataPtr(item);
			}
			else
			{
				m_ti.lpszText = L"";
			}
#else
			auto str = reinterpret_cast<char*>(cell->GetData());
			if (str)
			{
				//TRACE(L"%ls\n", str);
				static WCHAR buf[MAX_BUFFER_FOR_TOOLTIP];
				auto p = JD::to_wstring(str);
				auto pp = p.c_str();
				lstrcpyW(buf, pp);
				m_ti.lpszText = buf; // const_cast<LPWSTR>(pp); //  L"Hola Grid!";              //     GetItemDataPtr(item);
//#define JDH
#ifdef JDH
				::AfxMessageBox(buf);
#endif
			}
			else
			{
				const wchar_t* p = _T("");
				m_ti.lpszText = const_cast<wchar_t*>(p);
			}
#endif
			m_Tip.SendMessage(TTM_UPDATETIPTEXT, 0, (LPARAM)&m_ti);
			m_Tip.SendMessage(TTM_TRACKPOSITION, 0, (LPARAM)MAKELONG(ptScreen.x + 10, ptScreen.y - 20));
		}
		else
		{
			const wchar_t* p = _T("");
			m_ti.lpszText = const_cast<wchar_t*>(p);
			m_Tip.SendMessage(TTM_UPDATETIPTEXT, 0, (LPARAM)&m_ti);
		}
	}
}

void CJDGridCtrl::PreSubclassWindow()
{
	m_Tip.Create(this, WS_POPUP | TTS_ALWAYSTIP);

	m_ti.cbSize = sizeof(TOOLINFO);
	m_ti.hinst = AfxGetInstanceHandle();

	m_ti.hwnd = GetSafeHwnd();
	m_ti.uId = (UINT_PTR)GetSafeHwnd();
	m_ti.uFlags = TTF_IDISHWND | TTF_TRACK | TTF_ABSOLUTE;
	const wchar_t* p = _T("");
	m_ti.lpszText = const_cast<wchar_t*>(p); // _T("");

	GetClientRect(&m_ti.rect);

	m_Tip.SendMessage(TTM_ADDTOOL, 0, (LPARAM)&m_ti);
}


BEGIN_MESSAGE_MAP(CJDGridCtrl, CGridCtrl)
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CJDGridCtrl message handlers


