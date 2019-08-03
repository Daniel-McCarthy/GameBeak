#ifndef COLORDIALOG_H
#define COLORDIALOG_H

#include <QDialog>
#include <QFile>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QPushButton>
#include "src/Gpu.h"

namespace Ui {
class ColorDialog;
}

struct PaletteSelection {
    QString paletteName;
    int paletteIndex;
};

class PaletteListView;
class ColorSelectorWidget;
class ColorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorDialog(QWidget *parent, Gpu* gpu);
    void loadPalettes();
    void setPalettePreviews(int index);
    void setPreviewColor(ColorSelectorWidget* colorWidget, QColor& color);
    void setPalette();
    void overwriteGPUPaletteAtIndexWithCurrentPalette(int index);
    void indexChanged(int row, int column);
    ~ColorDialog();

public slots:
    void listDataChanged();
    void resetButtonClicked();

private:
    Gpu* gpu;
    Ui::ColorDialog *ui;
    QAction* selectAction;
    PaletteSelection defaultPalette = {"Default Palette", 0};
    PaletteSelection currentSelection = defaultPalette;
};

#endif // COLORDIALOG_H
