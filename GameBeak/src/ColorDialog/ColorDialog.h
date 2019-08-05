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
    void addNewPalette();
    void deleteCurrentPalette();
    void overwriteGPUPaletteAtIndexWithCurrentPalette(int index);
    void indexChanged(int row, int column);
    void savePalettesToFile();
    ~ColorDialog();

public slots:
    void resetButtonClicked();
    void listItemRenamed(QStandardItem* item);

private:
    Gpu* gpu;
    Ui::ColorDialog *ui;
    QAction* selectAction;
};

#endif // COLORDIALOG_H
