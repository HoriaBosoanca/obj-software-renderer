#define SDL_MAIN_HANDLED
#include <SDL.h>
#include "../backend.h"

SDL_Window* window;
SDL_Surface* surface;
uint32_t* pixels;

static void clear_screen(const Color& col) {
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			set_pixel(x, y, col);
}

void init() {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(
		"obj software renderer",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIDTH, HEIGHT,
		0
	);
	surface = SDL_GetWindowSurface(window);
	pixels = static_cast<uint32_t*>(surface->pixels);
	SDL_LockSurface(surface);
	clear_screen(BLACK);
}

void set_pixel(const int x, const int y, const Color& col) {
	if (0 <= x && x < WIDTH && 0 <= y && y < HEIGHT) {
		pixels[(HEIGHT-1-y) * WIDTH + x] = SDL_MapRGB(surface->format, col.r, col.g, col.b);
	}
}

void render() {
	SDL_UnlockSurface(surface);
	SDL_UpdateWindowSurface(window);
	SDL_Event event;
	while (event.type != SDL_QUIT)
		SDL_PollEvent(&event);
	SDL_DestroyWindow(window);
	SDL_Quit();
}