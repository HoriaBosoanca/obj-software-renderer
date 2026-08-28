#include "draw.h"
#include "backend.h"
#include <algorithm>
#include <cmath>

static void bad_draw_line(const Vec2 A, const Vec2 B, const Color& col) {
	for (float t = 0; t < 1; t+=.02) {
		const int x = std::round(A.x+(B.x-A.x)*t);
		const int y = std::round(A.y+(B.y-A.y)*t);
		set_pixel(x, y, col);
	}
}

static void better_draw_line(Vec2 A, Vec2 B, const Color& col) {
	const bool steep = std::abs(A.x-B.x) < std::abs(A.y-B.y);
	if (steep) {
		std::swap(A.x, A.y);
		std::swap(B.x, B.y);
	}
	if (A.x > B.x) {
		std::swap(A, B);
	}
	for (int x = A.x; x <= B.x; x++) {
		const float t = (x-A.x)/(B.x-A.x);
		const int y = std::round(A.y+(B.y-A.y)*t);
		if (steep) {
			set_pixel(y, x, col);
		} else {
			set_pixel(x, y, col);
		}
	}
}

void draw_triangle_empty(const Triangle2D& t, const Color& col) {
	better_draw_line(t.A, t.B, col);
	better_draw_line(t.B, t.C, col);
	better_draw_line(t.C, t.A, col);
}

static void scanline_fill_triangle(const Triangle2D& t, const Color& col) {
	Vec2 A = t.A, B = t.B, C = t.C;
	if (A.y < B.y) std::swap(A, B);
	if (A.y < C.y) std::swap(A, C);
	if (B.y < C.y) std::swap(B, C);
	// A top, B mid, C bottom
	const float mab = (A.y-B.y)/(A.x-B.x),
				mac = (A.y-C.y)/(A.x-C.x),
				mbc = (B.y-C.y)/(B.x-C.x);
	for (float yi = A.y; yi >= B.y; yi -= 0.02f) {
		// d: y-yi=0, so y=yi this is the scan-line at height yi
		// AB: y-ya=mab*(x-xa)
		// the intersection of d and AB is the start point of the scan-line
		float x1 = (yi-A.y)/mab+A.x;
		// AC: y-ya=mac*(x-xa)
		// the intersection of d and AC is the end point of the scan-line
		float x2 = (yi-A.y)/mac+A.x;
		if (x1 > x2) std::swap(x1, x2);
		for (float xi = x1; xi <= x2; xi += 0.02f) {
			set_pixel(xi, yi, col);
		}
	}
	for (float yi = B.y; yi >= C.y; yi -= 0.02f) {
		float x1 = (yi-B.y)/mbc+B.x;
		float x2 = (yi-A.y)/mac+A.x;
		if (x1 > x2) std::swap(x1, x2);
		for (float xi = x1; xi <= x2; xi += 0.02f) {
			set_pixel(xi, yi, col);
		}
	}
}

static void bbox_fill_triangle(const Triangle2D& t, const Color& col) {
	const Vec2 A = t.A, B = t.B, C = t.C;
	const Vec3 bbmin = {
		std::min(std::min(A.x, B.x), C.x),
		std::min(std::min(A.y, B.y), C.y),
		0
	}, bbmax = {
		std::max(std::max(A.x, B.x), C.x),
		std::max(std::max(A.y, B.y), C.y),
		0
	};
#pragma omp parallel for
	for (int x = bbmin.x; x <= bbmax.x; x++) {
		for (int y = bbmin.y; y <= bbmax.y; y++) {
			set_pixel(x, y, col);
		}
	}
}

void draw_triangle_fill(const Triangle2D& t, const Color& col) {
	bbox_fill_triangle(t, col);
}