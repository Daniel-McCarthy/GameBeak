#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QImage>
#include <QGraphicsView>

class Canvas : public QGraphicsView
{
public:
    Canvas(QWidget* parent = 0);
    ~Canvas();
    QGraphicsScene *scene;

public slots:
    void drawImage(QImage image);
};

#endif // CANVAS_H
