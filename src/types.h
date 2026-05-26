#pragma once
#include <cstdint>

struct Point {
	Point(int _x, int _y)
		: x(_x), y(_y) {}
	int x, y;
};

struct Color {
	Color(uint8_t _b, uint8_t _g, uint8_t _r, uint8_t _a)
		: b(_b), g(_g), r(_r), a(_a) {}
	uint8_t b, g, r, a;
};

const Color
	WHITE   = {255, 255, 255, 255},
	GREEN   = {  0, 255,   0, 255},
	RED     = {  0,   0, 255, 255},
	BLUE    = {255, 128,  64, 255},
	YELLOW  = {  0, 200, 255, 255};