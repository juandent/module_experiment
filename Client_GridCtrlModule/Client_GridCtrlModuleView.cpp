
// Client_GridCtrlModuleView.cpp : implementation of the CClientGridCtrlModuleView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Client_GridCtrlModule.h"
#endif

#include "Client_GridCtrlModuleDoc.h"
#include "Client_GridCtrlModuleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CClientGridCtrlModuleView

IMPLEMENT_DYNCREATE(CClientGridCtrlModuleView, CView)

BEGIN_MESSAGE_MAP(CClientGridCtrlModuleView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CClientGridCtrlModuleView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CClientGridCtrlModuleView construction/destruction

CClientGridCtrlModuleView::CClientGridCtrlModuleView() noexcept
{
	// TODO: add construction code here

}

CClientGridCtrlModuleView::~CClientGridCtrlModuleView()
{
}

BOOL CClientGridCtrlModuleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CClientGridCtrlModuleView drawing

void CClientGridCtrlModuleView::OnDraw(CDC* /*pDC*/)
{
	CClientGridCtrlModuleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CClientGridCtrlModuleView printing


void CClientGridCtrlModuleView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CClientGridCtrlModuleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CClientGridCtrlModuleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CClientGridCtrlModuleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CClientGridCtrlModuleView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CClientGridCtrlModuleView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CClientGridCtrlModuleView diagnostics

#ifdef _DEBUG
void CClientGridCtrlModuleView::AssertValid() const
{
	CView::AssertValid();
}

void CClientGridCtrlModuleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CClientGridCtrlModuleDoc* CClientGridCtrlModuleView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CClientGridCtrlModuleDoc)));
	return (CClientGridCtrlModuleDoc*)m_pDocument;
}
#endif //_DEBUG


// CClientGridCtrlModuleView message handlers
