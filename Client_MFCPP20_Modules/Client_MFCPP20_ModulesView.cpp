
// Client_MFCPP20_ModulesView.cpp : implementation of the CClientMFCPP20ModulesView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Client_MFCPP20_Modules.h"
#endif

#include "Client_MFCPP20_ModulesDoc.h"
#include "Client_MFCPP20_ModulesView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientMFCPP20ModulesView

IMPLEMENT_DYNCREATE(CClientMFCPP20ModulesView, CView)

BEGIN_MESSAGE_MAP(CClientMFCPP20ModulesView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CClientMFCPP20ModulesView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CClientMFCPP20ModulesView construction/destruction

CClientMFCPP20ModulesView::CClientMFCPP20ModulesView() noexcept
{
	// TODO: add construction code here

}

CClientMFCPP20ModulesView::~CClientMFCPP20ModulesView()
{
}

BOOL CClientMFCPP20ModulesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CClientMFCPP20ModulesView drawing

void CClientMFCPP20ModulesView::OnDraw(CDC* /*pDC*/)
{
	CClientMFCPP20ModulesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CClientMFCPP20ModulesView printing


void CClientMFCPP20ModulesView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CClientMFCPP20ModulesView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CClientMFCPP20ModulesView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CClientMFCPP20ModulesView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CClientMFCPP20ModulesView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CClientMFCPP20ModulesView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CClientMFCPP20ModulesView diagnostics

#ifdef _DEBUG
void CClientMFCPP20ModulesView::AssertValid() const
{
	CView::AssertValid();
}

void CClientMFCPP20ModulesView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CClientMFCPP20ModulesDoc* CClientMFCPP20ModulesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClientMFCPP20ModulesDoc)));
	return (CClientMFCPP20ModulesDoc*)m_pDocument;
}
#endif //_DEBUG


// CClientMFCPP20ModulesView message handlers
