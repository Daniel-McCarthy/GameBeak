#pragma once

#include "Main.h"
#include <tuple>
#include <sstream>

using namespace sf;

#ifndef DEBUGGERH
#define DEBUGGERH

tuple<string, int> disassembleInstruction(short address);
bool checkForWriteBreakpoint(bool &writeBreakpoint, bool &writeBreakpointValue, byte &breakpointValue, short &writeBreakpointAddress);

#endif // !DEBUGGERH