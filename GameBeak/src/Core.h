#ifndef CORE_H
#define CORE_H

#include "src/Memory.h"
#include "src/Rom.h"
#include "src/Cpu.h"
#include "src/Input.h"
#include "src/Screen.h"
#include "src/Gpu.h"

#include "src/Mappers/MBC1.h"
#include "src/Mappers/MBC2.h"
#include "src/Mappers/MBC3.h"
#include "src/Mappers/MBC5.h"

#include <QWidget>

class Core : public QObject
{
    Q_OBJECT
public:
    explicit Core(QWidget *parent = 0);
    virtual ~Core();
    Memory* getMemoryPointer();
    Rom* getRomPointer();
    Cpu* getCPUPointer();
    Input* getInputPointer();
    Screen* getScreenPointer();
    Gpu* getGpuPointer();
    MBC1* getMBC1Pointer();
    MBC2* getMBC2Pointer();
    MBC3* getMBC3Pointer();
    MBC5* getMBC5Pointer();

    bool* getGBCModePointer();

    bool run = false;
    bool paused = false;
    bool step = false;
    bool enableInterruptsNextCycle = false;
    bool interruptNextCycle = false;
    bool repeatBug = false; //Halt bug

    int clocks = 4500;
    int memoryControllerMode = 0;

    //Settings values
    bool GBCMode = false;					//This controls whether Gameboy Color emulation is currently activated.
    bool ForceDMGMode = false;				//This allows forcing games to run in DMG emulation.

    void emulationLoop();

private:
    Screen screen;
    Rom rom;
    Cpu cpu;
    Gpu gpu;
    Input input;
    Memory memory;

    MBC1 mbc1;
    MBC2 mbc2;
    MBC3 mbc3;
    MBC5 mbc5;

    bool soundEnabled = false;
    bool tileDrawMode = false;
    bool fullMapScreenMode = false;

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
