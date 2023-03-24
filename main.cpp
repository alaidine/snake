#include <SDL2/SDL.h>
#include <iostream>

int main() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to initialize the SDL2 library" << std::endl;
		return -1;
	}

	SDL_Window *window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 680, 480, 0);
	if (!window) {
		std::cout << "Failed to create window" << std::endl;
		return -1;
	}

	// renderer is to draw on the window
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		std::cout << "Failed to create renderer" << std::end;
		return -1;
	}

	// window_surface is to render an image into the screen
	SDL_Surface *window_surface = SDL_GetWindowSurface(window);
	if(!window_surface) {
		std::cout << "Failed to get the surface from the window" << std::endl;
		return -1;
	}

	// main loop
	bool keep_window_open = true;
	while(keep_window_open) {
		SDL_Event e;
		while(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					keep_window_open = false;
					break;
			}
		}
		SDL_UpdateWindowSurface(window);
	}

	return 0;
}