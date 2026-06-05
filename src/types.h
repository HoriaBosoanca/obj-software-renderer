#pragma once
#include <cstdint>
#include <utility>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 800;

struct Vec3 {
	float x, y, z;
	Vec3(const float _x, const float _y, const float _z)
		: x(_x), y(_y), z(_z) {}
	Vec3 operator+(const float n) const {
		return Vec3{x+n, y+n, z+n};
	}
	Vec3 operator/(const float n) const {
		return Vec3{x/n, y/n, z/n};
	}
};

using Triangle = std::tuple<Vec3, Vec3, Vec3>;

struct Color {
	Color(const uint8_t _b, const uint8_t _g, const uint8_t _r, const uint8_t _a)
		: b(_b), g(_g), r(_r), a(_a) {}
	uint8_t b, g, r, a;
};

const Color
	WHITE   = {255, 255, 255, 255},
	GREEN   = {  0, 255,   0, 255},
	RED     = {  0,   0, 255, 255},
	BLUE    = {255, 128,  64, 255},
	YELLOW  = {  0, 200, 255, 255};