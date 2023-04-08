#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

int main() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to initialize the SDL2 library" << std::endl;
		return -1;
	}

	SDL_Window *window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);
	if (!window) {
		std::cout << "Failed to create window" << std::endl;
		return -1;
	}

	// renderer is to draw on the window
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer) {
		std::cout << "Failed to create renderer" << std::endl;
		return -1;
	}

	enum Direction {
		DOWN,
		UP,
		LEFT,
		RIGHT
	};

	Direction dir = DOWN;

	SDL_Rect head {250, 250, 10, 10};

	std::deque<SDL_Rect> rq;
	int size = 1;

	// Create apples on the map
	std::vector<SDL_Rect> apples;
	for (int i = 0; i < 100; i++) {
		apples.emplace_back(rand()%100*10, rand()%100*10, 10, 10);
	}

	bool keep_window_open = true;
	while(keep_window_open) {
		SDL_Event e;

		// Check input
		while(SDL_PollEvent(&e)) {
			switch(e.type) {
				case SDL_QUIT:
					keep_window_open = false;
					break;

				case SDL_KEYDOWN:
					switch(e.key.keysym.sym) {
						case SDLK_DOWN:
							dir = DOWN;
							break;
						case SDLK_UP:
							dir = UP;
							break;
						case SDLK_LEFT:
							dir = LEFT;
							break;
						case SDLK_RIGHT:
							dir = RIGHT;
							break;
				}
					
			}
		}

		// Move
		switch(dir) {
			case DOWN:
				head.y += 5;
				break;
			case UP:
				head.y -= 5;
				break;
			case LEFT:
				head.x -= 5;
				break;
			case RIGHT:
				head.x += 5;
				break;
		}

		// Clear Window with a color
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// Draw the body
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &head);

		// Present the renderer to show what has been drawn
		SDL_RenderPresent(renderer);
		SDL_Delay(25);
	}
}
