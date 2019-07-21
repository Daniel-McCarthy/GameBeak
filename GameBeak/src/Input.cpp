#include "Input.h"
#include "Core.h"
#include "Memory.h"
#include "Cpu.h"

//Gameboy keys:
//[Up][Left][Right][Down][A][B][Start][Select]

//Mapped to standard keyboard keys:
//[Up][Left][Right][Down][Z][X][Enter][RShift]

Input::Input(QObject *parent, Memory& memory, Cpu& cpu)
    : QObject(parent), memory(memory), cpu(cpu)
{
}

unsigned char Input::getKeyInput()
{
    return memory.readMemory(0xFF00);
}

bool Input::isAnyKeyPressed()
{
	return keyUp || keyDown || keyLeft || keyRight || keyStart || keySelect || keyA || keyB;
}

void Input::readInput()
{
    unsigned char keyInput = getKeyInput();
	bool interrupt = false;
    cpu.setStop(false);

	if (((keyInput & 0x10) >> 4) == 1)
	{

		if (keyA) { //Z //A
			keyInput &= 0xFE;
			interrupt = true;
		}
		else
		{
			keyInput |= 0x01;
		}

		if (keyB) { //X //B
			keyInput &= 0xFD;
			interrupt = true;
		}
		else
		{
			keyInput |= 0x02;
		}

		if (keySelect) { //Control //Select
			keyInput &= 0xFB;
			interrupt = true;
		}
		else
		{
			keyInput |= 0x04;
		}

		if (keyStart) { //Enter //Start
			keyInput &= 0xF7;
			interrupt = true;
		}
		else
		{
			keyInput |= 0x08;
		}

	}
	else if (((keyInput & 0x20) >> 5) == 1)//(keyInput == 0x20)
	{

		if (!(keyRight && keyLeft)) //Detect if both inputs are NOT enabled at once
		{
			if (keyRight)
			{
				keyInput &= 0xFE;
				interrupt = true;
			}
			else
			{
				keyInput |= 0x01;
			}

			if (keyLeft)
			{
				keyInput &= 0xFD;
				interrupt = true;
			}
			else
			{
				keyInput |= 0x02;
			}
		}
		else //To solve issue of multiple key input on one axis we will ignore input when both left and right are pressed at the same time.
		{
			keyInput |= 0x01;
			keyInput |= 0x02;
		}

		if (!(keyUp && keyDown)) //Detect if both inputs are NOT enabled at once
		{
			if (keyUp)
			{
				keyInput &= 0xFB;
				interrupt = true;
			}
			else
			{
				keyInput |= 0x04;
			}

			if (keyDown)
			{
				keyInput &= 0xF7;
				interrupt = true;
			}
			else
			{
				keyInput |= 0x08;
			}
		}
		else //To solve issue of multiple key input on one axis we will ignore input when both left and right are pressed at the same time.
		{
			keyInput |= 0x04;
			keyInput |= 0x08;
		}

	}
	else
	{
		keyInput |= 0x01;
		keyInput |= 0x02;
		keyInput |= 0x04;
		keyInput |= 0x08;
	}


	//Bit 7 and 6 are always 1
	keyInput |= 0x80; //Bit 7
	keyInput |= 0x40; //Bit 6

	if (interrupt)
	{
        memory.writeMemory(0xFF0F, (unsigned char)(memory.readMemory(0xFF0F) | 0x10));
	}

    memory.writeMemory(0xFF00, keyInput);
}

void Input::setKeyInput(int keyCode, bool enabled)
{
    cpu.setStop(false);

	switch (keyCode)
	{
	case 0:
	{
		keyUp = enabled;
		break;
	}
	case 1:
	{
		keyDown = enabled;
		break;
	}
	case 2:
	{
		keyLeft = enabled;
		break;
	}
	case 3:
	{
		keyRight = enabled;
		break;
	}
	case 4:
	{
		keyStart = enabled;
		break;
	}
	case 5:
	{
		keySelect = enabled;
		break;
	}
	case 6:
	{
		keyA = enabled;
		break;
	}
	case 7:
	{
		keyB = enabled;
		break;
	}
	}
}

bool Input::eventFilter(QObject *obj, QEvent *event) {
    bool keyPressed = event->type() == QEvent::KeyPress;
    bool keyReleased = event->type() == QEvent::KeyRelease;

    if (keyPressed || keyReleased) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        int key = keyEvent->key();

        if (key == Qt::Key_Z) {
            setKeyInput(6, keyPressed);
        }
        if (key == Qt::Key_X) {
            setKeyInput(7, keyPressed);
        }
        if (key == Qt::Key_Return) {
            setKeyInput(4, keyPressed);
        }
        if (key == Qt::Key_Shift) {
            setKeyInput(5, keyPressed);
        }
        if (key == Qt::Key_Right) {
            setKeyInput(3, keyPressed);
        }
        if (key == Qt::Key_Left) {
            setKeyInput(2, keyPressed);
        }
        if (key == Qt::Key_Up) {
            setKeyInput(0, keyPressed);
        }
        if (key == Qt::Key_Down) {
            setKeyInput(1, keyPressed);
        }
    }

    return QObject::eventFilter(obj, event);
}

