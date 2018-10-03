#pragma once

#ifndef INPUTH
#define INPUTH

#pragma once
class Cpu;
class Memory;
class Core;
class Input
{

private:
    Memory* memory;
    Cpu* cpu;

public:
	bool keyRight = false, keyLeft = false, keyUp = false, keyDown = false, keyStart = false, keySelect = false, keyA = false, keyB = false;

    unsigned char getKeyInput();
	bool isAnyKeyPressed();
	void readInput();
	void setKeyInput(int keyCode, bool enabled);
};

#endif // !INPUTH
