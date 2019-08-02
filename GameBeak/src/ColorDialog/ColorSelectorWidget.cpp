#include "ColorSelectorWidget.h"

ColorSelectorWidget::ColorSelectorWidget(QWidget* parent) : QWidget(parent)
{
}

void ColorSelectorWidget::setColor(QColor color) {
    QPalette widgetPalette = QWidget::palette();
    widgetPalette.setColor(QWidget::backgroundRole(), *(new QColor(color)));
    QWidget::setAutoFillBackground(true);
    QWidget::setPalette(widgetPalette);
}

QColor ColorSelectorWidget::getColor() {
    return QWidget::palette().background().color();
}

void ColorSelectorWidget::selectColorViaDialog() {
    QColor selectedColor = QColorDialog::getColor(getColor());
    if (selectedColor.isValid()) {
        setColor(selectedColor);
    }
}

void ColorSelectorWidget::mouseDoubleClickEvent(QMouseEvent* event) {
    selectColorViaDialog();
}
