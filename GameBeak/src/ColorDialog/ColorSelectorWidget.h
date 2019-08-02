#ifndef COLORSELECTORWIDGET_H
#define COLORSELECTORWIDGET_H

#include <QWidget>
#include <QColorDialog>

class ColorSelectorWidget : public QWidget
{
public:
    ColorSelectorWidget(QWidget* parent = 0);
    void selectColorViaDialog();
    void setColor(QColor color);
    QColor getColor();

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;

};
#endif // COLORSELECTORWIDGET_H
