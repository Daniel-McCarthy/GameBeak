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
    Memory* getMemoryPointer();
    Rom* getRomPointer();
    Cpu* getCPUPointer();

    bool* getGBCModePointer();

    bool run;
    bool paused;
    bool step;
    bool enableInterruptsNextCycle;
    bool repeatBug; //Halt bug
    bool ForceDMGMode;

private:
    Memory* memory = new Memory(this);
    Rom* rom = new Rom();
    Cpu* cpu = new Cpu(this);
    bool* GBCMode;

signals:

public slots:
};

#endif // CORE_H
