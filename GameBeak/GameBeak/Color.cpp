#include "Color.h"

Color Color::Black = Color(0, 0, 0, 255);

Color::Color()
{
	r = 0;
	g = 0;
	b = 0;
	a = 0;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	a = 0;
}

Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

int Color::getInt()
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

bool Color::operator==(Color& operand)
{
	if ((this->r == operand.r) && (this->g == operand.g) && (this->b == operand.b) && (this->a == operand.a))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Color::operator!=(Color& operand)
{
	return !(*this == operand);
}

void Color::operator*=(Color& operand)
{
	this->r *= operand.r;
	this->g *= operand.g;
	this->b *= operand.b;
}