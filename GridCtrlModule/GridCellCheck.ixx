module;


#include "MFCFramework.h"


export module GridCellCheck;

import GridCell;


export
{
    class  CGridCellCheck : public CGridCell
    {
        friend class CGridCtrl;
        DECLARE_DYNCREATE(CGridCellCheck)

    public:
        CGridCellCheck();

    public:
        BOOL SetCheck(BOOL bChecked = TRUE);
        BOOL GetCheck();

        // Operations
        virtual CSize GetCellExtent(CDC* pDC);
        virtual void OnClick(CPoint PointCellRelative);
        virtual BOOL GetTextRect(LPRECT pRect);

    protected:
        CRect GetCheckPlacement();

        virtual BOOL Draw(CDC* pDC, int nRow, int nCol, CRect rect, BOOL bEraseBkgnd = TRUE);

    protected:
        BOOL  m_bChecked;
        CRect m_Rect;
    };

}