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

    QImage image = QImage(320,288, QImage::Format_RGB32);
    image.fill(0xFF8080FF);
    canvas->drawImage(image);

    installEventFilter(core->getInputPointer());

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
    emit setEmulationRun(false);
    delete ui;

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

    delete core;
    delete canvas;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    this->~MainWindow();
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
