#include "Core.h"

Core::Core(QWidget *parent) : QWidget(parent) {}

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

bool* Core::getGBCModePointer() {
    return GBCMode;
}
