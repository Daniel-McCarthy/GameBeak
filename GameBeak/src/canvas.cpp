#include "canvas.h"

Canvas::Canvas(QWidget* parent)
    : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFocusPolicy(Qt::NoFocus);
}

Canvas::~Canvas() {
    delete scene;
}


void Canvas::drawImage(QImage image)
{
    image = image.scaled(320, 288, Qt::IgnoreAspectRatio);
    scene->clear();
    QPixmap pixmap = QPixmap::fromImage(image);
    scene->addPixmap(pixmap);
    setScene(scene);
    show();
}
