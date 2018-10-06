#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "src/Core.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    core = new Core();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    QString filePath = QFileDialog::getOpenFileName(this, ("Open GB File"),
                                                      "/home",
                                                      ("GameBoy Files (*.gb *.gbc)"));

    emit onGameFileOpened(filePath);
}
