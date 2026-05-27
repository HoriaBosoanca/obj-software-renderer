#pragma once
#include <cstdint>
#include <utility>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 800;

struct Point {
	Point(float _x, float _y)
		: x(_x), y(_y) {}
	void operator+(const float n) {
		x += n;
		y += n;
	}
	void operator/(const float n) {
		x /= n;
		y /= n;
	}
	float x, y;
};

using Line = std::pair<Point, Point>;

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