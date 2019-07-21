#include "Core.h"
#include <QCoreApplication>
#include <QTextStream>
#include <QtDebug>

{
    this->screen = screen;
}*/

/*Core::Core() {
//works
}*/

/*Core::Core(QWidget *parent,Screen* screen)
    : QWidget(parent),
    memory(rom, cpu, GBCMode),
    gpu(memory, *screen, GBCMode, paletteSetting),
    cpu(memory, input, enableInterruptsNextCycle, repeatBug),
    input(memory, cpu),
    rom()
{
    this->screen = screen;

    *//*this->memory = new Memory(this);
    this->gpu = new Gpu(this);
    this->cpu = new Cpu(this);
    this->input = new Input(this);
    this->rom = new Rom();*//*
}*/

Core::Core(QWidget *parent)
    : QObject(parent),
        screen(nullptr, memory, gpu),
        rom(this),
        cpu(memory, input, enableInterruptsNextCycle, repeatBug),
        gpu(memory, screen, GBCMode, paletteSetting),
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

