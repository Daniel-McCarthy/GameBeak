#pragma once

using namespace std;

#ifndef COLORH
#define COLORH

class Color
{
public:
	static Color Black;

	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;

	bool Color::operator!=(Color& operand);
	void Color::operator*=(Color& operand);

	Color();
	Color(unsigned char r, unsigned char g, unsigned char b);
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	int getInt();

	bool operator==(Color& operand);

	/*
	const Color operator*(const Color& lhs, const Color& rhs)
	{
		return Color(lhs.r * rhs.r, rhs.g * rhs.g, lhs.b * rhs.b);
	}
	*/

	friend Color operator*(Color& lhs, Color& rhs)
	{
		return Color(lhs.r * rhs.r, rhs.g * rhs.g, lhs.b * rhs.b);
	}

};

#endif