#ifndef CORE_H
#define CORE_H

#include "src/Memory.h"

#include <QWidget>

class Core : public QWidget
{
    Q_OBJECT
public:
    explicit Core(QWidget *parent = nullptr);

private:
    Memory* memory = new Memory();

signals:

public slots:
};

