#pragma once
#include <Windows.h>
#include <iostream>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <sstream>
#include <fstream>
#include <stack>
#include <vector>
#include <thread>

#include "GameWindow.h"
#include "gpu.h"
#include "sharpCPU.h"

using namespace std;
using namespace sf;

#pragma once
#ifndef  MAINH
#define MAINH

extern short regAF;
extern short regBC;
extern short regDE;
extern short regHL;

extern short memoryPointer;
extern short stackPointer;

#include "Memory.h"
extern Memory beakMemory;
extern GameWindow beakWindow;
extern gpu beakGPU;
extern sharpCPU cpu;
#include "Audio.h"
extern Audio beakAudio;
extern int memoryControllerMode;
extern bool run;
extern bool paused;
extern bool step;
extern bool interruptNextCycle;
extern byte paletteSetting;

#endif // ! MAINH