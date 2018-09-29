#ifndef CORE_H
#define CORE_H

#include "src/Memory.h"
#include "src/Rom.h"
#include "src/Cpu.h"

#include <QWidget>

class Core : public QWidget
{
    Q_OBJECT
public:
    explicit Core(QWidget *parent = nullptr);

private:
    Memory* memory = new Memory();
    Rom* rom = new Rom();
    Cpu* cpu = new Cpu();
    bool GBCMode;

signals:

public slots:
};

#endif // CORE_H
