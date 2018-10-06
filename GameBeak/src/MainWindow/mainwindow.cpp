#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Core.h"
#include "src/Memory.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    core = new Core();
    QObject::connect(this, &MainWindow::onGameFileOpened,
                             core->getMemoryPointer(), &Memory::romLoaded);
}

MainWindow::~MainWindow()
{
    delete ui;
    QObject::disconnect(this, &MainWindow::onGameFileOpened,
                        core->getMemoryPointer(), &Memory::romLoaded);
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, ("Open GB File"),
                                                      "/home",
                                                      ("GameBoy Files (*.gb *.gbc)"));

    emit onGameFileOpened(filePath);
}
