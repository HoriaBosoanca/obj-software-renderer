#pragma once
#include <cstdint>

constexpr int WIDTH = 800,
              HEIGHT = 800;
constexpr float CAM_SCALE = 1.0f;

struct Vec2 {
	float x, y;
	Vec2(const float _x, const float _y)
		: x(_x), y(_y) {}
	Vec2 operator+(const float n) const {
		return Vec2{x+n, y+n};
	}
	Vec2 operator/(const float n) const {
		return Vec2{x/n, y/n};
	}
	Vec2 operator*(const Vec2 v) const {
		return Vec2{x*v.x, y*v.y};
	}
};
struct Vec3 {
	float x, y, z;
	Vec3(const float _x, const float _y, const float _z)
		: x(_x), y(_y), z(_z) {}
	Vec2 to2D() const {
		return Vec2{x, y};
	}
};
struct Triangle2D {
	Vec2 A, B, C;
	Triangle2D(const Vec2 _a, const Vec2 _b, const Vec2 _c)
		: A{_a}, B{_b}, C{_c} {}
	Triangle2D operator+(const float n) const {
		return Triangle2D{A+n, B+n, C+n};
	}
	Triangle2D operator/(const float n) const {
		return Triangle2D{A/n, B/n, C/n};
	}
	Triangle2D operator*(const Vec2 v) const {
		return Triangle2D{A*v, B*v, C*v};
	}
};
struct Triangle3D {
	Vec3 A, B, C;
	Triangle3D(const Vec3 _a, const Vec3 _b, const Vec3 _c)
		: A{_a}, B{_b}, C{_c} {}
	Triangle2D to2D() const {
		return Triangle2D{A.to2D(), B.to2D(), C.to2D()};
	}
};

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
	YELLOW  = {  0, 200, 255, 255},
	BLACK   = {	 0,   0,   0,   0};