#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <cstdint>

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow(
		"obj software renderer",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600,
		0
	);

	SDL_Surface* surface = SDL_GetWindowSurface(window);
	bool run = true;
	while (run) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) run = false;
		}

		SDL_LockSurface(surface);
		const auto pixels = static_cast<uint32_t*>(surface->pixels);
		for (int y = 0; y < 600; y++)
			for (int x = 0; x < 800; x++)
				pixels[y * 800 + x] = SDL_MapRGB(surface->format, 0, 0, 0);
		SDL_UnlockSurface(surface);
		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}