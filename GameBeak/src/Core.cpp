#include "Core.h"
#include <QCoreApplication>
#include <QTextStream>
#include <QtDebug>

Core::Core(QWidget *parent)
    : QObject(parent),
        screen(nullptr, memory, gpu),
        rom(this),
        cpu(memory, input, enableInterruptsNextCycle, repeatBug),
        gpu(memory, screen, GBCMode),
        input(this, memory, cpu),
        memory(this, rom, cpu, GBCMode, ForceDMGMode, mbc1, mbc2, mbc3, mbc5),
        mbc1(memory, rom),
        mbc2(memory, rom),
        mbc3(memory, rom),
        mbc5(memory, rom)
{
    QObject::connect(&rom, &Rom::fullRomWrite,
                     &memory, &Memory::writeFullRomToRam);
    QObject::connect(&rom, &Rom::rom0Write,
                     &memory, &Memory::writeRom0ToRam);
    QObject::connect(&memory, &Memory::cpu_SetDoubleSpeedMode,
                     &cpu, &Cpu::setDoubleSpeedModeSignal);
}

Core::~Core() {
    QObject::disconnect(&rom, &Rom::fullRomWrite,
                     &memory, &Memory::writeFullRomToRam);
    QObject::disconnect(&rom, &Rom::rom0Write,
                     &memory, &Memory::writeRom0ToRam);
    QObject::disconnect(&memory, &Memory::cpu_SetDoubleSpeedMode,
                     &cpu, &Cpu::setDoubleSpeedModeSignal);
}


Memory* Core::getMemoryPointer() {
    return &memory;
}

Rom* Core::getRomPointer() {
    return &rom;
}

Cpu* Core::getCPUPointer() {
    return &cpu;
}

Input* Core::getInputPointer() {
    return &input;
}

Screen* Core::getScreenPointer() {
    return &screen;
}

Gpu* Core::getGpuPointer() {
    return &gpu;
}

bool* Core::getGBCModePointer() {
    return &GBCMode;
}

MBC1* Core::getMBC1Pointer() {
    return &mbc1;
}

MBC2* Core::getMBC2Pointer() {
    return &mbc2;
}

MBC3* Core::getMBC3Pointer() {
    return &mbc3;
}

MBC5* Core::getMBC5Pointer() {
    return &mbc5;
}

void Core::setPaused(bool setting) {
    paused = setting;
}

void Core::setRun(bool setting) {
    run = setting;
}

void Core::setStep(bool setting) {
    step = setting;
}

void Core::setForcedDMGMode(bool setting) {
    ForceDMGMode = setting;
}

void Core::emulationLoop() {
    rom.readRomHeader();
    GBCMode = (rom.isGBCRom() && !ForceDMGMode);

    if (GBCMode)
    {
        memory.initializeGameBoyColorValues();
    }
    else
    {
        memory.initializeGameBoyValues();
    }
    int clocksSinceLastTimerTIMAIncrement = 0;
    int clocksSinceLastTimerDIVIncrement = 0;
    int clocksSinceLastScanLineComplete = 0;
    int clocksSinceLastVBlank = 0;
    int clocksSinceLastScreenRefresh = 0;
    uint opcodeCounter = 0;
    while (run)
    {

        if (!paused || step)
        {
            input.readInput();
            if (!cpu.returnStop() && !cpu.checkForHaltOrInterrupt())
            {

                unsigned char opcode = memory.readMemory(memory.memoryPointer++); 

                cpu.selectOpcode(opcode);
                opcodeCounter++;

                if (repeatBug)
                {
                    memory.memoryPointer--;
                    repeatBug = false;
                }
            }
            else
            {
                if (cpu.returnStop())
                {
                    cpu.executeStop();
                }

                cpu.selectOpcode(0); //Gets stuck at a halt without this, because no cycles are occuring (no opcode is running) the vblank interrupt never occurs
            }


            step = false;
            clocks += cpu.tClock;
            cpu.updateTIMA(clocks, clocksSinceLastTimerTIMAIncrement, clocksSinceLastTimerDIVIncrement);
            screen.updateLCD(clocks, clocksSinceLastScanLineComplete, clocksSinceLastScreenRefresh, clocksSinceLastVBlank);
            cpu.mClock = 0;
            cpu.tClock = 0;
        }

        if (screen.processPolling || paused) {
            //Poll QT Events
            QCoreApplication::processEvents();
            screen.processPolling = false;
        }
    }
}
