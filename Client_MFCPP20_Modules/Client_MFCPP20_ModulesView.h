
// Client_MFCPP20_ModulesView.h : interface of the CClientMFCPP20ModulesView class
//

#pragma once


class CClientMFCPP20ModulesView : public CView
{
protected: // create from serialization only
	CClientMFCPP20ModulesView() noexcept;
	DECLARE_DYNCREATE(CClientMFCPP20ModulesView)

// Attributes
public:
	CClientMFCPP20ModulesDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CClientMFCPP20ModulesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Client_MFCPP20_ModulesView.cpp
inline CClientMFCPP20ModulesDoc* CClientMFCPP20ModulesView::GetDocument() const
   { return reinterpret_cast<CClientMFCPP20ModulesDoc*>(m_pDocument); }
#endif

