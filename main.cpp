#include <iostream>

#include <SDL/SDL.h>

#include "game.h"

using namespace std;
using namespace gs;

const int WIDTH = 1280;
const int HEIGHT = 720;
const int BPP = 32;
const int DELAY = 40;

int main(int argc, char* argv[])
{
	SDL_Surface* background = 0;
	bool running = true;
	SDL_Event event;

	SDL_Init(SDL_INIT_EVERYTHING);

	background = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_SWSURFACE);
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				running = false;
		}
		SDL_Flip(background);
	}

	SDL_Quit();

	return 0;
}
