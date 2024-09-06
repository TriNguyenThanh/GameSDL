#include <SDL.h>

int main(int arc, char* argv[]) {
	SDL_Window* window = SDL_CreateWindow("Test IDE",
	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_SHOWN);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Rect rect = { 100, 100, 100, 100 };
	
	return 0;
}