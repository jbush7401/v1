#include <SDL3/SDL.h>

int main(int argc, char* argv[]) {
	// Initialize SDL
	if(!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return -1;
	}
	
	// SDL_Createwindow
	SDL_Window* window = SDL_CreateWindow("My SDL Window",
		800,
		600,
		0);

	// Check if the window was created successfully
	if (!window) {
		SDL_Log("Failed to create window: %s", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	// Renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, nullptr);
	if (!renderer) {
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}

	SDL_SetRenderVSync(renderer, 1);

	bool running = true;
	while (running) {
		// Handle events
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				running = false;
			}
		}

		// Clear the screen
		SDL_SetRenderDrawColor(renderer, 50, 50, 150, 255);
		SDL_RenderClear(renderer);

		// Present the backbuffer
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}