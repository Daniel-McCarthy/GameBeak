#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <QDialog>
#include <QFile>
#include <QStandardItem>
#include <QStandardItemModel>
#include "src/Gpu.h"

namespace Ui {
class PaletteListView;
class ColorDialog;
}

struct PaletteSelection {
    QString paletteName;
    int paletteIndex;
};

class ColorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorDialog(QWidget *parent, Gpu* gpu);
    void loadPalettes();
    void setPalettePreviews(int index);
    void setPreviewColor(QWidget*& colorWidget, QColor& color);
    void indexChanged(int row, int column);
    ~ColorDialog();

private:
    Gpu* gpu;
    Ui::ColorDialog *ui;
    PaletteSelection defaultPalette = {"Default Palette", 0};
    PaletteSelection currentSelection = defaultPalette;
};

#endif // COLORDIALOG_H
