#ifndef CORE_H
#define CORE_H

#include "src/Memory.h"
#include "src/Rom.h"
#include "src/Cpu.h"
#include "src/Input.h"
#include "src/Screen.h"

#include <QWidget>

class Core : public QWidget
{
    Q_OBJECT
public:
    explicit Core(QWidget *parent = nullptr);
    Memory* getMemoryPointer();
    Rom* getRomPointer();
    Cpu* getCPUPointer();
    Input* getInputPointer();

    bool* getGBCModePointer();

    bool run;
    bool paused;
    bool step;
    bool enableInterruptsNextCycle = false;
    bool interruptNextCycle = false;
    bool repeatBug; //Halt bug

    short memoryPointer = 0x100;
    short stackPointer = 0;
    //Settings values
    bool GBCMode = false;					//This controls whether Gameboy Color emulation is currently activated.
    bool ForceDMGMode = false;				//This allows forcing games to run in DMG emulation.
    unsigned char paletteSetting = gamebeakPinkAlt;

private:
    Memory* memory = new Memory(this);
    Rom* rom = new Rom();
    Cpu* cpu = new Cpu(this);
    Input* input = new Input(this);
    Screen* screen = new Screen(this);


    enum paletteSettings
    {
        blackAndWhite,
        greenDMG,
        gamebeakPink,
        gamebeakPinkAlt,
        ultraPink,
        grapeCherry,
        mintPink,
        kigb,
        bgbm,
        noCashGMB,
        playGuy,
        dreamGBC,
        heboWIN,
        fpgaBoy,
    };

signals:

public slots:
    void setPaused(bool setting);
    void setRun(bool setting);
    void setStep(bool setting);
    void setForcedDMGMode(bool setting);
};

#endif // CORE_H
