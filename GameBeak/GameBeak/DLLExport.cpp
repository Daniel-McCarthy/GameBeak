#include <stdio.h>
#include "Main.h"

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

	__declspec(dllexport) Image getScreenData()
	{
		return beakWindow.screen;
	}

	__declspec(dllexport) void setRom(byte* rom, int romSize)
	{
		beakMemory.loadRom(rom, romSize);
	}

	__declspec(dllexport) void initiateEmulator()
	{
		startEmulator();
	}
}
