#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <cstdint>

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
#define CHANNELS 3

int main() {
	uint8_t pixels[WIDTH*HEIGHT*CHANNELS] = {};
	stbi_write_png("render.png", WIDTH, HEIGHT, CHANNELS,
		pixels, WIDTH*CHANNELS);
	return 0;
}