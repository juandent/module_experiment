module;


#include "MFCFramework.h"


export module TitleTip;



export
{

	// #define TITLETIP_CLASSNAME _T("ZTitleTip")
	constexpr auto TITLETIP_CLASSNAME = _T("ZTitleTip");

	/////////////////////////////////////////////////////////////////////////////
	// CTitleTip window

	class CTitleTip : public CWnd
	{
		// Construction
	public:
		CTitleTip();
		virtual ~CTitleTip();
		virtual BOOL Create(CWnd* pParentWnd);

		// Attributes
	public:
		void SetParentWnd(CWnd* pParentWnd) { m_pParentWnd = pParentWnd; }
		CWnd* GetParentWnd() { return m_pParentWnd; }

		// Operations
	public:
		void Show(CRect rectTitle, LPCTSTR lpszTitleText,
			int xoffset = 0, LPRECT lpHoverRect = NULL,
			const LOGFONT* lpLogFont = NULL,
			COLORREF crTextClr = CLR_DEFAULT, COLORREF crBackClr = CLR_DEFAULT);
		void Hide();

		// Overrides
			// ClassWizard generated virtual function overrides
			//{{AFX_VIRTUAL(CTitleTip)
	public:
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		virtual BOOL DestroyWindow();
		//}}AFX_VIRTUAL

	// Implementation
	protected:
		CWnd* m_pParentWnd;
		CRect  m_rectTitle;
		CRect  m_rectHover;
		DWORD  m_dwLastLButtonDown;
		DWORD  m_dwDblClickMsecs;
		BOOL   m_bCreated;

		// Generated message map functions
	protected:
		//{{AFX_MSG(CTitleTip)
		afx_msg void OnMouseMove(UINT nFlags, CPoint point);
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	};
}
