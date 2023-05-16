#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QHBoxLayout>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class Rom;
class Screen;
class Core;
class Canvas;
class ColorDialog;
class MemoryViewer;
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
    QHBoxLayout* hLayout;
    ColorDialog* currentColorDialog = nullptr;
    MemoryViewer* currentMemoryViewer = nullptr;

    void closeEvent(QCloseEvent *event);
    void terminateEmulation();
private slots:
    void on_actionOpen_triggered();
    void on_actionForce_DMG_triggered();
    void on_actionAutomatic_Selection_triggered();
    void on_actionPalette_triggered();
    void on_actionPause_triggered();
    void on_actionResume_triggered();
    void on_actionCreateSave_triggered();
    void on_actionMemory_Viewer_triggered();
    void paletteWindowClosed();
    void startEmulationThread();
    void endEmulationThread();

signals:
    void onGameFileOpened(QString filePath);
    void setEmulationPaused(bool setting);
    void setEmulationRun(bool setting);
    void createSaveFile(bool overwriteExisting);
};

#endif // MAINWINDOW_H
