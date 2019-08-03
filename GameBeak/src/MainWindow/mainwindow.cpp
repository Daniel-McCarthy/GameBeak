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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    core = new Core();
    canvas = new Canvas(this);
    canvas->move(0,21);
    canvas->resize(320,288);
    canvas->stackUnder(ui->menuBar);
    ui->menuBar->raise();


    setWindowIcon(QIcon(":/src/ICON1.ico"));

    hLayout = new QHBoxLayout(ui->centralWidget);
    hLayout->addWidget(canvas);

    QImage image = QImage(320,288, QImage::Format_RGB32);
    image.fill(0xFF8080FF);
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
    QString filePath = QFileDialog::getOpenFileName(this, ("Open GB File"),
                                                      "/home",
                                                      ("GameBoy Files (*.gb *.gbc)"));
    if (filePath != "") {
        emit onGameFileOpened(filePath);
    }
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

    currentColorDialog->loadPalettes();
    currentColorDialog->show();
}

void MainWindow::paletteWindowClosed() {
    QObject::disconnect(currentColorDialog, &ColorDialog::finished,
                        this, &MainWindow::paletteWindowClosed);

    delete currentColorDialog;
    currentColorDialog = NULL;
}
