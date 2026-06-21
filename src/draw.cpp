#include "draw.h"
#include "impl.h"
#include <cmath>
#include <tuple>

void draw_line(Vec3 a, Vec3 b, const Color c) {
	// for (float t = 0; t < 1; t+=.02) {
	// 	int x = std::round(a.x+(b.x-a.x)*t);
	// 	int y = std::round(a.y+(b.y-a.y)*t);
	// 	set_pixel_impl(x, y, color);
	// }
	const bool steep = std::abs(a.x-b.x) < std::abs(a.y-b.y);
	if (steep) {
		std::swap(a.x, a.y);
		std::swap(b.x, b.y);
	}
	if (a.x > b.x) {
		std::swap(a, b);
	}
	for (int x = a.x; x <= b.x; x++) {
		const float t = (x-a.x)/(b.x-a.x);
		const int y = std::round(a.y+(b.y-a.y)*t);
		if (steep) {
			set_pixel(y, x, c);
		} else {
			set_pixel(x, y, c);
		}
	}
}

void draw_triangle_wireframe(const Triangle& t, const Color c) {
	draw_line(std::get<0>(t), std::get<1>(t), c);
	draw_line(std::get<1>(t), std::get<2>(t), c);
	draw_line(std::get<2>(t), std::get<0>(t), c);
}

void draw_triangle_fill(const Triangle& t, const Color col) {
	Vec3 A = std::get<0>(t), B = std::get<1>(t), C = std::get<2>(t);
	if (A.y < B.y) std::swap(A, B);
	if (A.y < C.y) std::swap(A, C);
	if (B.y < C.y) std::swap(B, C);
	// A top, B mid, C bottom
	const float mab = (A.y-B.y)/(A.x-B.x),
				mac = (A.y-C.y)/(A.x-C.x),
				mbc = (B.y-C.y)/(B.x-C.x);
	for (float yi = A.y; yi >= B.y; yi -= 0.02f) {
		// d: y-yi=0, so y=yi this is the scan-line at height yi
		// AB: y-ya=mab(x-xa)
		// the intersection of d and AB is the start point of the scan-line
		float x1 = (yi-A.y)/mab+A.x;
		// AC: y-ya=mac(x-xa)
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