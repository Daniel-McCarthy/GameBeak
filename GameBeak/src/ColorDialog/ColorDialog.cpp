#include "ColorDialog.h"
#include "ui_ColorDialog.h"
#include "PaletteListView.h"
#include "ColorSelectorWidget.h"

ColorDialog::ColorDialog(QWidget *parent, Gpu* gpu) :
    QDialog(parent),
    ui(new Ui::ColorDialog)
{
    ui->setupUi(this);
//    ui->listView->setEditTriggers(QAbstractItemView.NoEditTriggers);
    this->gpu = gpu;

    ui->listView->setContextMenuPolicy(Qt::ActionsContextMenu);
    selectAction = new QAction ("Select Palette", this);
    ui->listView->addAction(selectAction);

    QObject::connect(selectAction, &QAction::triggered,
                        this, &ColorDialog::setPalette);
    QObject::connect(ui->listView, &PaletteListView::selectedIndexChanged,
                        this, &ColorDialog::indexChanged);
    QObject::connect(ui->listView, &PaletteListView::paletteDataChanged,
                        this, &ColorDialog::listDataChanged);
    QObject::connect(ui->buttonBox->button(QDialogButtonBox::Reset), &QPushButton::pressed,
                        this, &ColorDialog::resetButtonClicked);
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

void ColorDialog::setPreviewColor(ColorSelectorWidget* colorWidget, QColor& color) {
    colorWidget->setColor(color);
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

void ColorDialog::listDataChanged() {
    QModelIndex currentIndex = ui->listView->currentIndex();
    if (currentIndex.row() == currentSelection.paletteIndex) {
        QString currentPaletteName = currentIndex.data().toString();
        if (currentPaletteName != currentSelection.paletteName) {
            currentSelection.paletteName = currentPaletteName;
        }
    }
}

void ColorDialog::resetButtonClicked() {
    loadPalettes();
}

//void ColorDialog::setPalette(QModelIndex& index) {
void ColorDialog::setPalette() {
    int paletteRow = ui->listView->currentIndex().row();

    if (gpu->gameBeakPalette.length() > paletteRow) {
        gpu->gameBeakPalette[paletteRow].paletteColors[0] = ui->bg0ColorWidget0->getColor();
        gpu->gameBeakPalette[paletteRow].paletteColors[1] = ui->bg0ColorWidget1->getColor();
        gpu->gameBeakPalette[paletteRow].paletteColors[2] = ui->bg0ColorWidget2->getColor();
        gpu->gameBeakPalette[paletteRow].paletteColors[3] = ui->bg0ColorWidget3->getColor();

        gpu->gameBeakPalette[paletteRow].paletteColors[4] = ui->bp0ColorWidget0->getColor();
        gpu->gameBeakPalette[paletteRow].paletteColors[5] = ui->bp0ColorWidget1->getColor();
        gpu->gameBeakPalette[paletteRow].paletteColors[6] = ui->bp0ColorWidget2->getColor();
        gpu->gameBeakPalette[paletteRow].paletteColors[7] = ui->bp0ColorWidget3->getColor();

        gpu->gameBeakPalette[paletteRow].paletteColors[8] = ui->bp1ColorWidget0->getColor();
        gpu->gameBeakPalette[paletteRow].paletteColors[9] = ui->bp1ColorWidget1->getColor();
        gpu->gameBeakPalette[paletteRow].paletteColors[10] = ui->bp1ColorWidget2->getColor();
        gpu->gameBeakPalette[paletteRow].paletteColors[11] = ui->bp1ColorWidget3->getColor();
    }
    gpu->paletteSetting = paletteRow;
}

ColorDialog::~ColorDialog()
{
    QObject::connect(selectAction, &QAction::triggered,
                        this, &ColorDialog::setPalette);

    QObject::disconnect(ui->listView, &PaletteListView::selectedIndexChanged,
                        this, &ColorDialog::indexChanged);

    QObject::disconnect(ui->listView, &PaletteListView::paletteDataChanged,
                        this, &ColorDialog::listDataChanged);

    QObject::disconnect(ui->buttonBox->button(QDialogButtonBox::Reset), &QPushButton::pressed,
                        this, &ColorDialog::resetButtonClicked);

    delete ui;
}
