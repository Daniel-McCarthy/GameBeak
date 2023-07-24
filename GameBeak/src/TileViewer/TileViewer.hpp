#ifndef TILEVIEWER_H
#define TILEVIEWER_H

#include <QDialog>

namespace Ui {
class TileViewer;
}

class Memory;
class TileViewer : public QDialog
{
    Q_OBJECT

public:
    explicit TileViewer(QWidget *parent, Memory* memory);;
    ~TileViewer();

public slots:
    void on_refreshButton_clicked();

private:
    void renderTiles(QByteArray tileData);
    void readTileDataAndRefresh();
    QPixmap createPixmapFromTileBytes(QByteArray tileBytes);
    Memory* memory;
    Ui::TileViewer *ui;
};

#endif // TILEVIEWER_H
