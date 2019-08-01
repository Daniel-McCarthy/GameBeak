#include "ColorDialog.h"
#include "ui_ColorDialog.h"

ColorDialog::ColorDialog(QWidget *parent, Gpu* gpu) :
    QDialog(parent),
    ui(new Ui::ColorDialog)
{
    ui->setupUi(this);
    this->gpu = gpu;
}

void ColorDialog::loadPalettes() {
    QFile* palettesFile = new QFile(gpu->openCreatePalettesXML());
    gpu->loadPalettesFromXML(palettesFile);

    QStandardItemModel* itemModel = new QStandardItemModel(gpu->paletteNames.count(), 1, this);

    for(int i = 0; i < gpu->paletteNames.count(); i++)
    {
        QStandardItem* paletteName = new QStandardItem(gpu->paletteNames[i]);
        itemModel->setItem(i, paletteName);
    }

    ui->listView->setModel(itemModel);

    //Set first palette to preview
    setPalettePreviews(0);


    //To Do: Consider storing the name and index of the previously selected palette, then after reloading the palettes check if the index corresponds
    // to a palette of the same name. If so, keep the index where it was. If the index corresponds to something else, set it to 0.
    delete palettesFile;
}

void ColorDialog::setPalettePreviews(int index) {
    if (index > -1)
    {
        setPreviewColor(ui->bg0ColorWidget0, gpu->gameBeakPalette[(index * 12) + 0]);
        setPreviewColor(ui->bg0ColorWidget1, gpu->gameBeakPalette[(index * 12) + 1]);
        setPreviewColor(ui->bg0ColorWidget2, gpu->gameBeakPalette[(index * 12) + 2]);
        setPreviewColor(ui->bg0ColorWidget3, gpu->gameBeakPalette[(index * 12) + 3]);

        setPreviewColor(ui->bp0ColorWidget0, gpu->gameBeakPalette[(index * 12) + 4]);
        setPreviewColor(ui->bp0ColorWidget1, gpu->gameBeakPalette[(index * 12) + 5]);
        setPreviewColor(ui->bp0ColorWidget2, gpu->gameBeakPalette[(index * 12) + 6]);
        setPreviewColor(ui->bp0ColorWidget3, gpu->gameBeakPalette[(index * 12) + 7]);

        setPreviewColor(ui->bp1ColorWidget0, gpu->gameBeakPalette[(index * 12) + 8]);
        setPreviewColor(ui->bp1ColorWidget1, gpu->gameBeakPalette[(index * 12) + 9]);
        setPreviewColor(ui->bp1ColorWidget2, gpu->gameBeakPalette[(index * 12) + 10]);
        setPreviewColor(ui->bp1ColorWidget3, gpu->gameBeakPalette[(index * 12) + 11]);
    }
    else
    {
        QColor white = QColor(255, 255, 255, 255);
        setPreviewColor(ui->bg0ColorWidget0, white);
        setPreviewColor(ui->bg0ColorWidget1, white);
        setPreviewColor(ui->bg0ColorWidget2, white);
        setPreviewColor(ui->bg0ColorWidget3, white);

        setPreviewColor(ui->bp0ColorWidget0, white);
        setPreviewColor(ui->bp0ColorWidget1, white);
        setPreviewColor(ui->bp0ColorWidget2, white);
        setPreviewColor(ui->bp0ColorWidget3, white);

        setPreviewColor(ui->bp1ColorWidget0, white);
        setPreviewColor(ui->bp1ColorWidget1, white);
        setPreviewColor(ui->bp1ColorWidget2, white);
        setPreviewColor(ui->bp1ColorWidget3, white);
    }
}

void ColorDialog::setPreviewColor(QWidget*& colorWidget, QColor& color) {
    QPalette widgetPalette = colorWidget->palette();
    widgetPalette.setColor(colorWidget->backgroundRole(), *(new QColor(color)));
    colorWidget->setAutoFillBackground(true);
    colorWidget->setPalette(widgetPalette);
}

ColorDialog::~ColorDialog()
{
    delete ui;
}
