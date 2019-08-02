#ifndef COLORSELECTORWIDGET_H
#define COLORSELECTORWIDGET_H

#include <QWidget>

class ColorSelectorWidget : public QWidget
{
public:
    ColorSelectorWidget(QWidget* parent = 0);
    void setColor(QColor color);
    QColor getColor();
};

#endif // COLORSELECTORWIDGET_H
