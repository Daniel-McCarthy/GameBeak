#pragma once

#ifndef INPUTH
#define INPUTH

#include <QObject>
#include <QtGamepad/QGamepadManager>
#include <QtGamepad/QGamepad>

#pragma once
class Cpu;
class Memory;
class Core;
class Input : public QObject
{
    Q_OBJECT
private:
    void gamepadButtonPressed(int id, QGamepadManager::GamepadButton button, double value);
    void gamepadButtonReleased(int id, QGamepadManager::GamepadButton button);
    Memory& memory;
    Cpu& cpu;

public:
	bool keyRight = false, keyLeft = false, keyUp = false, keyDown = false, keyStart = false, keySelect = false, keyA = false, keyB = false;
    bool padRight = false, padLeft = false, padUp = false, padDown = false, padStart = false, padSelect = false, padA = false, padB = false;

    unsigned char getKeyInput();
    Input(QObject *parent, Memory& memory, Cpu& cpu);
    ~Input();
	bool isAnyKeyPressed();
	void readInput();
	void setKeyInput(int keyCode, bool enabled);
protected:
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // !INPUTH
