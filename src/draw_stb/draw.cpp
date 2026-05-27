#include "draw.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <cstdint>

#define CHANNELS 3
uint8_t pixels[WIDTH*HEIGHT*CHANNELS] = {};

#define IMAGE_OUT_PATH "../out/render.png"
void create_image() {
	stbi_write_png(IMAGE_OUT_PATH, WIDTH, HEIGHT, CHANNELS, pixels, WIDTH*CHANNELS);
}

void set_pixel(int x, int y, Color color) {
	int idx = ((HEIGHT-1-y)*WIDTH+x)*CHANNELS;
	pixels[idx + 0] = color.r;
	pixels[idx + 1] = color.g;
	pixels[idx + 2] = color.b;
}

void draw_line(Point a, Point b, Color color) {
	// for (float t = 0; t < 1; t+=.02) {
	// 	int x = std::round(a.x+(b.x-a.x)*t);
	// 	int y = std::round(a.y+(b.y-a.y)*t);
	// 	set_pixel(x, y, color);
	// }
	bool steep = std::abs(a.x-b.x) < std::abs(a.y-b.y);
	if (steep) {
		std::swap(a.x, a.y);
		std::swap(b.x, b.y);
	}
	if (a.x > b.x) {
		std::swap(a, b);
	}
	for (int x = a.x; x <= b.x; x++) {
		float t = (x-a.x)/static_cast<float>(b.x-a.x);
		int y = std::round(a.y+(b.y-a.y)*t);
		if (steep) {
			set_pixel(y, x, color);
		} else {
			set_pixel(x, y, color);
		}
	}
}