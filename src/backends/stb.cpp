#include "../backend.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define CHANNELS 3
static uint8_t pixels[WIDTH_PX*HEIGHT_PX*CHANNELS] = {};

void init() {}

void set_pixel(const int x, const int y, const Color& col) {
	if (0 <= x && x < WIDTH_PX && 0 <= y && y < HEIGHT_PX) {
		const int idx = ((HEIGHT_PX-1-y)*WIDTH_PX+x)*CHANNELS;
		pixels[idx + 0] = col.r;
		pixels[idx + 1] = col.g;
		pixels[idx + 2] = col.b;
	}
}

void render() {
	stbi_write_png("render.png", WIDTH_PX, HEIGHT_PX, CHANNELS, pixels, WIDTH_PX*CHANNELS);
}