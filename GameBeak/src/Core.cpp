#include "Core.h"

Core::Core(QWidget *parent, Screen *screen) : QWidget(parent)
{
    this->screen = screen;
}

Memory* Core::getMemoryPointer() {
    return memory;
}

Rom* Core::getRomPointer() {
    return rom;
}

Cpu* Core::getCPUPointer() {
    return cpu;
}

Input* Core::getInputPointer() {
    return input;
}

Screen* Core::getScreenPointer() {
    return screen;
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

