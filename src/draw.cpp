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

void draw_triangle(const Triangle& t, const Color c) {
	draw_line(std::get<0>(t), std::get<1>(t), c);
	draw_line(std::get<1>(t), std::get<2>(t), c);
	draw_line(std::get<2>(t), std::get<0>(t), c);
}