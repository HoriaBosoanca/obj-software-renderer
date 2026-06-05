#include "draw.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <cstdint>
#include <tuple>

#define CHANNELS 3
uint8_t pixels[WIDTH*HEIGHT*CHANNELS] = {};

void render(const char* out_path) {
	stbi_write_png(out_path, WIDTH, HEIGHT, CHANNELS, pixels, WIDTH*CHANNELS);
}

void set_pixel(int x, int y, const Color color) {
	if (0 <= x && x < WIDTH && 0 <= y && y < HEIGHT) {
		const int idx = ((HEIGHT-1-y)*WIDTH+x)*CHANNELS;
		pixels[idx + 0] = color.r;
		pixels[idx + 1] = color.g;
		pixels[idx + 2] = color.b;
	}
}

void draw_line(Vec3 a, Vec3 b, const Color c) {
	// for (float t = 0; t < 1; t+=.02) {
	// 	int x = std::round(a.x+(b.x-a.x)*t);
	// 	int y = std::round(a.y+(b.y-a.y)*t);
	// 	set_pixel(x, y, color);
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