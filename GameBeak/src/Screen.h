#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QGraphicsView>

class Screen : public QGraphicsView
{
public:
    Screen(QWidget* parent = 0);
};

#endif // SCREEN_H
