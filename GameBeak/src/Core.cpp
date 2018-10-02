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

bool* Core::getGBCModePointer() {
    return GBCMode;
}
