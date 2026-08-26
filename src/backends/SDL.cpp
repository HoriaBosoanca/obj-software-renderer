#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "../backend.h"

SDL_Surface* surface;
static uint32_t* pixels;

void set_pixel(const int x, const int y, const Color color) {
	if (0 <= x && x < WIDTH && 0 <= y && y < HEIGHT) {
		pixels[(HEIGHT-1-y) * WIDTH + x] = SDL_MapRGB(surface->format, color.r, color.g, color.b);
	}
}

void render() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow(
		"obj software renderer",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIDTH, HEIGHT,
		0
	);
	surface = SDL_GetWindowSurface(window);
	pixels = static_cast<uint32_t*>(surface->pixels);

	bool run = true;
	while (run) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) run = false;
		}
		SDL_LockSurface(surface);

		for (int y = 0; y < HEIGHT; y++)
			for (int x = 0; x < WIDTH; x++)
				set_pixel(x, y, BLACK);

		SDL_UnlockSurface(surface);
		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
}