#pragma once

#include "Persistent_passwords.h"
#include "LocationGrid.h"


// ControlsTest form view

class ControlsTest : public CFormView
{
	DECLARE_DYNCREATE(ControlsTest)

protected:
	ControlsTest();           // protected constructor used by dynamic creation
	virtual ~ControlsTest();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ControlsTest };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	LocationGrid m_grid;
public:
	virtual void OnInitialUpdate();
private:
	CEdit m_id;
	
	CJDGridCtrl m_grid_passwords;
	std::unique_ptr< GridDisplayer<Password>> m_password_displayer;

	CListBox m_password_listbox;
	BoxContents<decltype(db), Password, &Password::id> m_passwordLB;
public:
	afx_msg void OnSelchangePasswords();
	afx_msg void OnGridStartSelChange(NMHDR* pNotifyStruct, LRESULT*);
private:
	CJDGridCtrl m_grid_simple;
	CButton m_check1;
public:
	afx_msg void OnClickedCheck1();
private:
	CButton m_one;
	CButton m_two;
	RadioButtonGroup m_group_one_two;
public:
	afx_msg void OnClickedRadio();
private:
	CDateTimeCtrl m_date_time;
public:
	afx_msg void OnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};


