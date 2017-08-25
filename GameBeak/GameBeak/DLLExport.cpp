#include <stdio.h>
#include "Main.h"
#include "Image.h"

extern "C"
{

	__declspec(dllexport) void setPauseState(bool pauseEnabled)
	{
		paused = pauseEnabled;
	}
	__declspec(dllexport) bool getPauseState()
	{
		return paused;
	}

	__declspec(dllexport) void setRunState(bool runEnabled)
	{
		run = runEnabled;
	}
	__declspec(dllexport) bool getRunState()
	{
		return run;
	}

	__declspec(dllexport) int* getRegisters()
	{
		static int registers[] = { regAF, regBC, regDE, regHL };
		return registers;
	}

	__declspec(dllexport) short getAF()
	{
		return regAF;
	}

	__declspec(dllexport) short getBC()
	{
		return regBC;
	}

	__declspec(dllexport) short getDE()
	{
		return regDE;
	}

	__declspec(dllexport) short getHL()
	{
		return regHL;
	}

	__declspec(dllexport) int* getStackValues()
	{
		static int stackValues[] = { stackPointer, beakMemory.readMemory(stackPointer) };
		return stackValues;
	}

	__declspec(dllexport) short getPC()
	{
		return memoryPointer;
	}

	__declspec(dllexport) int* getScreenPixelData()
	{
		static int* pixelData = beakWindow.screen.getIntArray();
		return beakWindow.screen.getIntArray();
	}

	__declspec(dllexport) int* getScreenDimensions()
	{
		static int dimensions[] = { beakWindow.screen.getSize().x, beakWindow.screen.getSize().y };
	
		return dimensions;
	}

	__declspec(dllexport) void setRom(byte* rom, int romSize)
	{
		beakMemory.loadRom(rom, romSize);
	}

	__declspec(dllexport) void setStep()
	{
		step = true;
	}

	__declspec(dllexport) byte readMemoryByte(short address)
	{
		return beakMemory.readMemory(address);
	}

	__declspec(dllexport) void initiateEmulator()
	{
		startEmulator();
	}

	__declspec(dllexport) void disassembleAddress(short& address, char* cString, int& stringLength)
	{
		tuple<string, int> disassembledTuple = disassembleInstruction(address);

		address += get<1>(disassembledTuple);

		string disassembledString = get<0>(disassembledTuple);
		stringLength = disassembledString.length();

		for (int i = 0; i < 100; i++)
		{
			if (i < disassembledString.length())
			{
				cString[i] = (char)disassembledString[i];
			}
			else
			{
				cString[i] = NULL;
			}
		}
	}
}
