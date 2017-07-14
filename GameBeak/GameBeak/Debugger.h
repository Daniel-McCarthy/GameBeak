#pragma once

#include "Main.h"
#include <tuple>
#include <sstream>

using namespace sf;

#ifndef DEBUGGERH
#define DEBUGGERH

tuple<string, int> disassembleInstruction(short address);

#endif // !DEBUGGERH