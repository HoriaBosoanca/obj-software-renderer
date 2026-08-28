#include "../backend.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define CHANNELS 3
static uint8_t pixels[WIDTH*HEIGHT*CHANNELS] = {};

void init() {}

void set_pixel(const int x, const int y, const Color& col) {
	if (0 <= x && x < WIDTH && 0 <= y && y < HEIGHT) {
		const int idx = ((HEIGHT-1-y)*WIDTH+x)*CHANNELS;
		pixels[idx + 0] = col.r;
		pixels[idx + 1] = col.g;
		pixels[idx + 2] = col.b;
	}
}

void render() {
	stbi_write_png("render.png", WIDTH, HEIGHT, CHANNELS, pixels, WIDTH*CHANNELS);
}