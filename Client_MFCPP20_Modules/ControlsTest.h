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
};


