module;


#include "MFCFramework.h"


export module GridCellNumeric;

import GridCell;

export
{
    class CGridCellNumeric : public CGridCell
    {
        DECLARE_DYNCREATE(CGridCellNumeric)

    public:
        virtual BOOL Edit(int nRow, int nCol, CRect rect, CPoint point, UINT nID, UINT nChar);
        virtual void EndEdit();

    };
}

