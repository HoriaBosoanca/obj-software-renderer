#include "impl.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define CHANNELS 3
uint8_t pixels[WIDTH*HEIGHT*CHANNELS] = {};

void set_pixel(const int x, const int y, const Color color) {
	if (0 <= x && x < WIDTH && 0 <= y && y < HEIGHT) {
		const int idx = ((HEIGHT-1-y)*WIDTH+x)*CHANNELS;
		pixels[idx + 0] = color.r;
		pixels[idx + 1] = color.g;
		pixels[idx + 2] = color.b;
	}
}

void render(const std::function<void()>& draw_code) {
	draw_code();
	stbi_write_png("render.png", WIDTH, HEIGHT, CHANNELS, pixels, WIDTH*CHANNELS);
}