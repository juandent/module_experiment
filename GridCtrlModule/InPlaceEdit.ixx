module;

#include "MFCFramework.h"


#include "TCHAR.h"



export module InPlaceEdit;


export class CInPlaceEdit : public CEdit
{
    // Construction
public:
    CInPlaceEdit(CWnd* pParent, CRect& rect, DWORD dwStyle, UINT nID,
        int nRow, int nColumn, CString sInitText, UINT nFirstChar);

    // Attributes
public:

    // Operations
public:
    void EndEdit();

    // Overrides
         // ClassWizard generated virtual function overrides
         //{{AFX_VIRTUAL(CInPlaceEdit)
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
    virtual void PostNcDestroy();
    //}}AFX_VIRTUAL

// Implementation
public:
    virtual ~CInPlaceEdit();

    // Generated message map functions
protected:
    //{{AFX_MSG(CInPlaceEdit)
    afx_msg void OnKillFocus(CWnd* pNewWnd);
    afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg UINT OnGetDlgCode();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()

private:
    int     m_nRow;
    int     m_nColumn;
    CString m_sInitText;
    UINT    m_nLastChar;
    BOOL    m_bExitOnArrows;
    CRect   m_Rect;
};

