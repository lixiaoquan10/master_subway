#ifndef CMYICONSTYLE_H
#define CMYICONSTYLE_H

#include <QCommonStyle>

class CMyIconStyle : public QCommonStyle
{
    Q_OBJECT
public:
    CMyIconStyle();
    int pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const;
};

#endif // CMYICONSTYLE_H
