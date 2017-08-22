#pragma once

#include "Main.h"
#include "Image.h"
#include "Color.h"

using namespace std;

#ifndef POSTPROCESSH
#define POSTPROCESSH

Color mixColors(Color color1, Color color2);
Color mixColors(Color color1, Color color2, float div);

Image filterSelect(Image screen, byte filterNumber);

Image eagleFilter(Image screen);
Image scale2XFilter(Image screen);
Image scale3XFilter(Image screen);
Image blurFilter(Image screen);
Image emboldenFilter(Image screen);
Image customFilter(Image screen);
Image zigZagFilter(Image screen);
Image rainbowFilter(Image screen);


#endif // !POSTPROCESSH