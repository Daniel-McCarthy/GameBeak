#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Core.h"
#include "src/Memory.h"
#include <QFileDialog>
#include <QThread>
#include <QLayout>
#include <QPushButton>
#include "src/canvas.h"
#include "src/Screen.h"
#include "src/Rom.h"
#include "src/ColorDialog/ColorDialog.h"
#include "src/MemoryViewer/MemoryViewer.h"
#include "src/TileViewer/TileViewer.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->actionResume->setVisible(false);
    ui->actionResume->setEnabled(false);
    ui->actionPause->setEnabled(false);

    core = new Core();
    canvas = new Canvas(this);
    canvas->move(0,21);
    canvas->resize(320,288);
    canvas->stackUnder(ui->menuBar);
    ui->menuBar->raise();


    setWindowIcon(QIcon(":/src/ICON1.ico"));

    hLayout = new QHBoxLayout(ui->centralWidget);
    hLayout->setContentsMargins(0,0,0,0);
    hLayout->addWidget(canvas);

    // Display purple and pink default background.
    QImage image = QImage(320,288, QImage::Format_RGB32);
    image.fill(QColor(255, 80, 160, 255));
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < 5; y++) {
            image.setPixel(x, y, 0xFF800080);
        }
    }
    canvas->drawImage(image);

    installEventFilter(core->getInputPointer());

    QObject::connect(core->getScreenPointer(), &Screen::drawImageToScreen,
                     canvas, &Canvas::drawImage);

    QObject::connect(this, &MainWindow::onGameFileOpened,
                             core->getMemoryPointer(), &Memory::romLoaded);

    QObject::connect(this, &MainWindow::setEmulationPaused,
                             core, &Core::setPaused);

    QObject::connect(this, &MainWindow::setEmulationRun,
                             core, &Core::setRun);

    QObject::connect(this, &MainWindow::createSaveFile,
                            core->getMemoryPointer(), &Memory::createSaveFile);

    QObject::connect(core->getMemoryPointer(), &Memory::setEmulationRun,
                     core, &Core::setRun);

    QObject::connect(core->getMemoryPointer(), &Memory::setEmulationRun,
                     this, &MainWindow::startEmulationThread);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete canvas;
    delete core;
    delete hLayout;
}

void MainWindow::terminateEmulation() {
    removeEventFilter(core->getInputPointer());
    emit setEmulationRun(false);

    QObject::disconnect(this, &MainWindow::onGameFileOpened,
                        core->getMemoryPointer(), &Memory::romLoaded);

    QObject::disconnect(this, &MainWindow::setEmulationPaused,
                             core, &Core::setPaused);

    QObject::disconnect(this, &MainWindow::setEmulationRun,
                             core, &Core::setRun);

    QObject::disconnect(this, &MainWindow::createSaveFile,
                            core->getMemoryPointer(), &Memory::createSaveFile);

    QObject::disconnect(core->getMemoryPointer(), &Memory::setEmulationRun,
                     core, &Core::setRun);

    QObject::disconnect(core->getMemoryPointer(), &Memory::setEmulationRun,
                     this, &MainWindow::startEmulationThread);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    this->terminateEmulation();
    event->accept();
}

void MainWindow::startEmulationThread() {
    core->emulationLoop();
}

void MainWindow::endEmulationThread() {
    emit setEmulationRun(false);
}

void MainWindow::on_actionOpen_triggered()
{
    bool alreadyEmulating = core->run;
    QString initialDirectory = QDir::homePath();
    if (initialDirectory == "" ) {
        initialDirectory = QFileInfo(QCoreApplication::applicationFilePath()).absolutePath();
    }

    QString filePath = QFileDialog::getOpenFileName(this, ("Open GB File"),
                                                      initialDirectory,
                                                      ("GameBoy Files (*.gb *.gbc)"));
    if (filePath != "") {
        if (alreadyEmulating) {
            // Reset all emulation state for a fresh start
            // before loading in a new rom and running.
            core->resetCore();
        }

        core->getMemoryPointer()->romLoaded(filePath);
        ui->actionPause->setEnabled(true);
        ui->actionResume->setEnabled(true);
        ui->actionCreateSave->setEnabled(core->getRomPointer()->usesSaveRam());
        core->setRun(true);
        core->setPaused(false);
        startEmulationThread();
    }
}

void MainWindow::on_actionCreateSave_triggered() {
    createSaveFile(true);
}

void MainWindow::on_actionForce_DMG_triggered() {
    core->ForceDMGMode = true;

    if (ui->actionForce_DMG->isChecked() == false)
        ui->actionForce_DMG->toggle();
    if (ui->actionAutomatic_Selection->isChecked() == true)
        ui->actionAutomatic_Selection->toggle();
}

void MainWindow::on_actionAutomatic_Selection_triggered() {
    core->ForceDMGMode = false;

    if (ui->actionForce_DMG->isChecked() == true)
        ui->actionForce_DMG->toggle();
    if (ui->actionAutomatic_Selection->isChecked() == false)
        ui->actionAutomatic_Selection->toggle();
}

void MainWindow::on_actionPalette_triggered() {
    if (currentColorDialog != NULL) {
        return;
    }

    currentColorDialog = new ColorDialog(this, core->getGpuPointer());

    QObject::connect(currentColorDialog, &ColorDialog::finished,
                     this, &MainWindow::paletteWindowClosed);

    currentColorDialog->show();
}

void MainWindow::paletteWindowClosed() {
    QObject::disconnect(currentColorDialog, &ColorDialog::finished,
                        this, &MainWindow::paletteWindowClosed);

    delete currentColorDialog;
    currentColorDialog = NULL;
}

void MainWindow::on_actionPause_triggered() {
    ui->actionPause->setVisible(false);
    ui->actionResume->setVisible(true);
    setEmulationPaused(true);
}

void MainWindow::on_actionResume_triggered() {
    ui->actionPause->setVisible(true);
    ui->actionResume->setVisible(false);
    setEmulationPaused(false);
}

void MainWindow::on_actionMemory_Viewer_triggered() {
    if (currentMemoryViewer != NULL) {
        return;
    }

    currentMemoryViewer = new MemoryViewer(this, core->getMemoryPointer());

    currentMemoryViewer->show();
}

void MainWindow::on_actionTileViewer_triggered() {
    if (currentTileViewer != NULL) {
        return;
    }

    currentTileViewer = new TileViewer(this, core->getMemoryPointer());

    QObject::connect(currentTileViewer, &TileViewer::finished,
                        this, &MainWindow::tileViewerWindowClosed);

    currentTileViewer->show();
}


void MainWindow::tileViewerWindowClosed() {
    QObject::disconnect(currentTileViewer, &TileViewer::finished,
                        this, &MainWindow::tileViewerWindowClosed);

    delete currentTileViewer;
    currentTileViewer = NULL;
}
