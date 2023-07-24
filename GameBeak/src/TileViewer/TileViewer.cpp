#include "TileViewer.hpp"
#include "ui_TileViewer.h"
#include "../Memory.h"
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

TileViewer::TileViewer(QWidget *parent, Memory* memory) :
    QDialog(parent),
    ui(new Ui::TileViewer)
{
    ui->setupUi(this);

    this->memory = memory;

    QObject::connect(ui->refreshButton, &QPushButton::pressed,
                     this, &TileViewer::on_refreshButton_clicked);
}

TileViewer::~TileViewer()
{
    QObject::disconnect(ui->refreshButton, &QPushButton::pressed,
                     this, &TileViewer::on_refreshButton_clicked);

    delete ui;
}

void TileViewer::on_refreshButton_clicked()
{
    readTileDataAndRefresh();
}

void TileViewer::readTileDataAndRefresh() {
    unsigned int baseAddress = 0x8000;
    unsigned int bytesPerTile = 16;
    unsigned int numberOfTiles = 360;
    QByteArray ramTileData = memory->readDirectRamBytes(baseAddress, numberOfTiles * bytesPerTile);
    renderTiles(ramTileData);
}

void TileViewer::renderTiles(QByteArray tileData)
{
    // Create a new QGraphicsScene
    QGraphicsScene* scene = new QGraphicsScene();

    // Iterate over the tile data and create QGraphicsPixmapItems for each tile
    for (int i = 0; i < tileData.size(); i += 16)
    {
        QByteArray tileBytes = tileData.mid(i, 16);
        QPixmap pixmap = createPixmapFromTileBytes(tileBytes);

        QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(pixmap);
        pixmapItem->setPos((i / 16) % 20 * 8, (i / 16) / 20 * 8);

        // Add the pixmap item to the scene
        scene->addItem(pixmapItem);
    }


    // Set the created scene to the QGraphicsView
    ui->tilesGraphicsView->setScene(scene);
}

QPixmap TileViewer::createPixmapFromTileBytes(QByteArray tileBytes)
{
    // Convert the tile bytes to QImage
    QImage tileImage(8, 8, QImage::Format_Grayscale8);
    for (int y = 0; y < 8; ++y)
    {
        uchar* scanLine = tileImage.scanLine(y);
        for (int x = 0; x < 8; ++x)
        {
            uchar pixel = ((tileBytes[y * 2] >> (7 - x)) & 1) |
                          (((tileBytes[y * 2 + 1] >> (7 - x)) & 1) << 1);
            uchar palette[] = {0xFF, 0xAA, 0x55, 0};
            scanLine[x] = palette[pixel];  // Scale the pixel value to 0-255 range
        }
    }

    // Convert the QImage to QPixmap
    QPixmap pixmap = QPixmap::fromImage(tileImage);
    return pixmap;
}
