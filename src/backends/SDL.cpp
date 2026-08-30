#define SDL_MAIN_HANDLED
#include <SDL3/SDL.h>
#include "../backend.h"

static SDL_Window* window;
static SDL_Surface* surface;
static const SDL_PixelFormatDetails* fmt;
static uint32_t* pixels;

static void clear_screen(const Color& col) {
	for (int y = 0; y < HEIGHT_PX; y++)
		for (int x = 0; x < WIDTH_PX; x++)
			set_pixel(x, y, col);
}

void init() {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(
		"obj software renderer",
		WIDTH_PX, HEIGHT_PX,
		0
	);
	surface = SDL_GetWindowSurface(window);
	fmt = SDL_GetPixelFormatDetails(surface->format);
	pixels = static_cast<uint32_t*>(surface->pixels);
	SDL_LockSurface(surface);
	clear_screen(BLACK);
}

void set_pixel(const int x, const int y, const Color& col) {
	if (0 <= x && x < WIDTH_PX && 0 <= y && y < HEIGHT_PX) {
		pixels[(HEIGHT_PX-1-y) * WIDTH_PX + x] = SDL_MapRGB(fmt, nullptr, col.r, col.g, col.b);
	}
}

void render() {
	SDL_UnlockSurface(surface);
	SDL_UpdateWindowSurface(window);
	SDL_Event event{};
	while (event.type != SDL_EVENT_QUIT)
		SDL_PollEvent(&event);
	SDL_DestroyWindow(window);
	SDL_Quit();
}