#pragma once
#include <Windows.h>
#include <iostream>
#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>


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

extern bool run;
extern bool paused;
extern bool step;
extern bool enableInterruptsNextCycle;
extern bool repeatBug; //Halt bug
extern bool GBCMode;
extern bool ForceDMGMode;
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
#include "Rom.h"
extern Rom rom;
#include "Mapper.h"
extern Mapper mapper;
#include "MBC1.h"
extern MBC1 mbc1;
#include "MBC2.h"
extern MBC2 mbc2;
#include "MBC3.h"
extern MBC3 mbc3;
#include "MBC5.h"
extern MBC5 mbc5;
#include "Input.h"
extern Input beakInput;

#endif // ! MAINH