#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

namespace Ui {
class MainWindow;
}

class Rom;
class Screen;
class Core;
class Canvas;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Core* core = nullptr;
    Canvas* canvas;

    void closeEvent(QCloseEvent *event);
    void terminateEmulation();
private slots:
    void on_actionOpen_triggered();
    void startEmulationThread();
    void endEmulationThread();

signals:
    void onGameFileOpened(QString filePath);
    void setEmulationPaused(bool setting);
    void setEmulationRun(bool setting);
};

#endif // MAINWINDOW_H
