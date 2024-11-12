#include "cmyiconstyle.h"

CMyIconStyle::CMyIconStyle() :
    QCommonStyle()
{
}

int CMyIconStyle::pixelMetric(QStyle::PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    int n;
//    int n = QPlastiqueStyle::pixelMetric(metric, option, widget);
    if(metric == QStyle::PM_SmallIconSize)
        n = 32;
    return n;
}
