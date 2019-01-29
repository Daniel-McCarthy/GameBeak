#pragma once

#ifndef INPUTH
#define INPUTH

#include <QObject>

#pragma once
class Cpu;
class Memory;
class Core;
class Input : public QObject
{
    Q_OBJECT
private:
    Memory& memory;
    Cpu& cpu;

public:
	bool keyRight = false, keyLeft = false, keyUp = false, keyDown = false, keyStart = false, keySelect = false, keyA = false, keyB = false;

    unsigned char getKeyInput();
    Input(QObject *parent, Memory& memory, Cpu& cpu);
	bool isAnyKeyPressed();
	void readInput();
	void setKeyInput(int keyCode, bool enabled);
};

#endif // !INPUTH
