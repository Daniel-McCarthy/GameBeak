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

    loadPalettes();

    QObject::connect(selectAction, &QAction::triggered,
                        this, &ColorDialog::setPalette);
    QObject::connect(ui->listView, &PaletteListView::selectedIndexChanged,
                        this, &ColorDialog::indexChanged);
    QObject::connect(ui->buttonBox->button(QDialogButtonBox::Reset), &QPushButton::pressed,
                        this, &ColorDialog::resetButtonClicked);
    QObject::connect(ui->saveToFileButton, &QPushButton::pressed,
                        this, &ColorDialog::savePalettesToFile);
    QObject::connect(ui->newPaletteButton, &QPushButton::pressed,
                        this, &ColorDialog::addNewPalette);
    QObject::connect(ui->deletePaletteButton, &QPushButton::pressed,
                        this, &ColorDialog::deleteCurrentPalette);
    QObject::connect(qobject_cast<QStandardItemModel*>(ui->listView->model()), &QStandardItemModel::itemChanged,
                        this, &ColorDialog::listItemRenamed);
}

void ColorDialog::addNewPalette() {
    // Add new palette item to QListView.
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->listView->model());
    model->appendRow(new QStandardItem("New Palette"));

    // Add new palette to GPU palette list to match.
    Palette newPalette = gpu->defaultPalette;
    gpu->gameBeakPalette.push_back(newPalette);

    // Select/highlight the new item in the QListView and scroll to it.
    QModelIndex newSelectionIndex = model->index(model->rowCount() - 1, 0, QModelIndex());
    ui->listView->setCurrentIndex(newSelectionIndex);
    ui->listView->selectionModel()->select(newSelectionIndex, QItemSelectionModel::Select);
    ui->listView->scrollTo(newSelectionIndex);
}

void ColorDialog::deleteCurrentPalette() {
    int currentIndex = ui->listView->currentIndex().row();
    if (currentIndex >= 0 && currentIndex < gpu->gameBeakPalette.count()) {
        ui->listView->model()->removeRow(currentIndex, ui->listView->model()->index(currentIndex, 1, QModelIndex()));
        gpu->gameBeakPalette.removeAt(currentIndex);
    }
}

void ColorDialog::listItemRenamed(QStandardItem* item) {
    int rowIndex = item->row();

    if (rowIndex >= 0 && rowIndex < gpu->gameBeakPalette.count()) {
        QString newName = item->text();
        if (newName.length() > 0) {
            gpu->gameBeakPalette[rowIndex].paletteName = newName;
        }
        else {
            QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->listView->model());
            QString originalName = gpu->gameBeakPalette[rowIndex].paletteName;
            model->item(rowIndex, 0)->setText(originalName);
        }
    }
}

void ColorDialog::loadPalettes() {
    QFile* palettesFile = new QFile(gpu->openCreatePalettesXML());
    gpu->loadPalettesFromXML(palettesFile);

    QStandardItemModel* itemModel = new QStandardItemModel(gpu->gameBeakPalette.count(), 1, this);

    for(int i = 0; i < gpu->gameBeakPalette.count(); i++)
    {
        QStandardItem* paletteName = new QStandardItem(gpu->gameBeakPalette[i].paletteName);
        itemModel->setItem(i, paletteName);
    }

    ui->listView->setModel(itemModel);

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
    int selectedIndex = row;
    if (selectedIndex >= 0 && selectedIndex < gpu->gameBeakPalette.count()) {
        setPalettePreviews(selectedIndex);
    }
}

void ColorDialog::resetButtonClicked() {
    QStandardItemModel* model = qobject_cast<QStandardItemModel*>(ui->listView->model());
    QString currentPaletteName = ui->listView->currentIndex().data().toString();

    loadPalettes();

    QList<QStandardItem*> matches = model->findItems(currentPaletteName);
    if (matches.count() > 0) {
        QModelIndex indexOfMatch = matches[0]->index();
        ui->listView->setCurrentIndex(indexOfMatch);
        ui->listView->selectionModel()->select(indexOfMatch, QItemSelectionModel::Select);
        ui->listView->scrollTo(indexOfMatch);
        setPalettePreviews(indexOfMatch.row());
    }
}

//void ColorDialog::setPalette(QModelIndex& index) {
void ColorDialog::setPalette() {
    int paletteRow = ui->listView->currentIndex().row();
    overwriteGPUPaletteAtIndexWithCurrentPalette(paletteRow);

    gpu->paletteSetting = paletteRow;
}

void ColorDialog::overwriteGPUPaletteAtIndexWithCurrentPalette(int index) {
    if (gpu->gameBeakPalette.length() > index) {
        gpu->gameBeakPalette[index].paletteColors[0] = ui->bg0ColorWidget0->getColor();
        gpu->gameBeakPalette[index].paletteColors[1] = ui->bg0ColorWidget1->getColor();
        gpu->gameBeakPalette[index].paletteColors[2] = ui->bg0ColorWidget2->getColor();
        gpu->gameBeakPalette[index].paletteColors[3] = ui->bg0ColorWidget3->getColor();

        gpu->gameBeakPalette[index].paletteColors[4] = ui->bp0ColorWidget0->getColor();
        gpu->gameBeakPalette[index].paletteColors[5] = ui->bp0ColorWidget1->getColor();
        gpu->gameBeakPalette[index].paletteColors[6] = ui->bp0ColorWidget2->getColor();
        gpu->gameBeakPalette[index].paletteColors[7] = ui->bp0ColorWidget3->getColor();

        gpu->gameBeakPalette[index].paletteColors[8] = ui->bp1ColorWidget0->getColor();
        gpu->gameBeakPalette[index].paletteColors[9] = ui->bp1ColorWidget1->getColor();
        gpu->gameBeakPalette[index].paletteColors[10] = ui->bp1ColorWidget2->getColor();
        gpu->gameBeakPalette[index].paletteColors[11] = ui->bp1ColorWidget3->getColor();
    }
}

void ColorDialog::savePalettesToFile() {
    // Update GPU palettes with current selected palette.
    int paletteRow = ui->listView->currentIndex().row();
    overwriteGPUPaletteAtIndexWithCurrentPalette(paletteRow);

    // Write all GPU palettes to palettes.xml.
    gpu->savePalettesToFile();
}

ColorDialog::~ColorDialog()
{
    QObject::disconnect(selectAction, &QAction::triggered,
                        this, &ColorDialog::setPalette);

    QObject::disconnect(ui->listView, &PaletteListView::selectedIndexChanged,
                        this, &ColorDialog::indexChanged);

    QObject::disconnect(ui->buttonBox->button(QDialogButtonBox::Reset), &QPushButton::pressed,
                        this, &ColorDialog::resetButtonClicked);

    QObject::disconnect(ui->saveToFileButton, &QPushButton::pressed,
                        this, &ColorDialog::savePalettesToFile);

    QObject::disconnect(ui->newPaletteButton, &QPushButton::pressed,
                        this, &ColorDialog::addNewPalette);

    QObject::disconnect(ui->deletePaletteButton, &QPushButton::pressed,
                        this, &ColorDialog::deleteCurrentPalette);

    QObject::connect(qobject_cast<QStandardItemModel*>(ui->listView->model()), &QStandardItemModel::itemChanged,
                        this, &ColorDialog::listItemRenamed);

    ui->listView->removeAction(selectAction);
    delete selectAction;
    delete ui;
}
