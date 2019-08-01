#include "ColorDialog.h"
#include "ui_ColorDialog.h"
#include "PaletteListView.h"

ColorDialog::ColorDialog(QWidget *parent, Gpu* gpu) :
    QDialog(parent),
    ui(new Ui::ColorDialog)
{
    ui->setupUi(this);
//    ui->listView->setEditTriggers(QAbstractItemView.NoEditTriggers);
    this->gpu = gpu;

    QObject::connect(ui->listView, &PaletteListView::selectedIndexChanged,
                        this, &ColorDialog::indexChanged);
}

void ColorDialog::loadPalettes() {
    QFile* palettesFile = new QFile(gpu->openCreatePalettesXML());
    gpu->loadPalettesFromXML(palettesFile);

    QStandardItemModel* itemModel = new QStandardItemModel(gpu->gameBeakPalette.count(), 1, this);

    for(int i = 0; i < gpu->gameBeakPalette.count(); i++)
    {
//        paletteNameListBox.Items.Add(paletteNames[i]);
//        ui->listView->it
        QStandardItem* paletteName = new QStandardItem(gpu->gameBeakPalette[i].paletteName);
        itemModel->setItem(i, paletteName);
    }

    ui->listView->setModel(itemModel);

    //
    if (itemModel->rowCount() > 0) {
        QString nameOfPreviousSelectedPalette = currentSelection.paletteName;
        QString currentNameAtLastSelectedIndex = (itemModel->rowCount() > currentSelection.paletteIndex) ? itemModel->item(currentSelection.paletteIndex, 0)->text() : "No Such Palette";

        // Keep previous selected index if the newly loaded palette at the same
        // index has the same name. Otherwise, reset the selection to 0.
        if (currentNameAtLastSelectedIndex != nameOfPreviousSelectedPalette) {
            currentSelection = {
                itemModel->item(0, 0)->text(),
                0
            };
        }
    } else {
        currentSelection = defaultPalette;
    }

    //Set first palette to preview
    setPalettePreviews(0);

//    paletteNameListBox.SelectedIndex = 0;

    //To Do: Consider storing the name and index of the previously selected palette, then after reloading the palettes check if the index corresponds
    // to a palette of the same name. If so, keep the index where it was. If the index corresponds to something else, set it to 0.
    delete palettesFile;
}

void ColorDialog::setPalettePreviews(int index) {
    if (index > -1)
    {
        setPreviewColor(ui->bg0ColorWidget0, gpu->gameBeakPalette[index].paletteColors[0]);
        setPreviewColor(ui->bg0ColorWidget1, gpu->gameBeakPalette[index].paletteColors[1]);
        setPreviewColor(ui->bg0ColorWidget2, gpu->gameBeakPalette[index].paletteColors[2]);
        setPreviewColor(ui->bg0ColorWidget3, gpu->gameBeakPalette[index].paletteColors[3]);

        setPreviewColor(ui->bp0ColorWidget0, gpu->gameBeakPalette[index].paletteColors[4]);
        setPreviewColor(ui->bp0ColorWidget1, gpu->gameBeakPalette[index].paletteColors[5]);
        setPreviewColor(ui->bp0ColorWidget2, gpu->gameBeakPalette[index].paletteColors[6]);
        setPreviewColor(ui->bp0ColorWidget3, gpu->gameBeakPalette[index].paletteColors[7]);

        setPreviewColor(ui->bp1ColorWidget0, gpu->gameBeakPalette[index].paletteColors[8]);
        setPreviewColor(ui->bp1ColorWidget1, gpu->gameBeakPalette[index].paletteColors[9]);
        setPreviewColor(ui->bp1ColorWidget2, gpu->gameBeakPalette[index].paletteColors[10]);
        setPreviewColor(ui->bp1ColorWidget3, gpu->gameBeakPalette[index].paletteColors[11]);
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

void ColorDialog::indexChanged(int row, int column) {
    int previousSelection = currentSelection.paletteIndex;
    if (row != -1 && gpu->gameBeakPalette.count() > row) {
        PaletteSelection newSelection = {
            gpu->gameBeakPalette[row].paletteName,
            row
        };
        currentSelection = newSelection;
    } else {
        currentSelection = defaultPalette;
    }

    if (previousSelection != currentSelection.paletteIndex) {
        setPalettePreviews(currentSelection.paletteIndex);
    }
}

ColorDialog::~ColorDialog()
{
    QObject::disconnect(ui->listView, &PaletteListView::selectedIndexChanged,
                        this, &ColorDialog::indexChanged);

    delete ui;
}