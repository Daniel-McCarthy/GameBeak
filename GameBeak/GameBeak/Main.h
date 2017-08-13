#pragma once
#include <Windows.h>
#include <iostream>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>

#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <list>
#include <thread>

#include "GameWindow.h"
#include "gpu.h"
#include "sharpCPU.h"

using namespace std;
using namespace sf;

#pragma once
#ifndef  MAINH
#define MAINH

//sfg::SFGUI sfGUI;

extern int clocks;

extern short regAF;
extern short regBC;
extern short regDE;
extern short regHL;

extern int memoryControllerMode;
extern bool run;
extern bool paused;
extern bool step;
extern bool enableInterruptsNextCycle;
extern byte paletteSetting;
extern byte filterSetting;

extern short memoryPointer;
extern short stackPointer;
extern GameWindow beakWindow;
extern sharpCPU cpu;
extern gpu beakGPU;
#include "Memory.h"
extern Memory beakMemory;
#include "Audio.h"
extern Audio beakAudio;

#endif // ! MAINH