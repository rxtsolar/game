#include <iostream>

#include "engine.h"

using namespace std;

namespace gs {

Engine::Engine(void)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		exit(1);

	running = false;
	width = DEF_WIDTH;
	height = DEF_HEIGHT;
	bpp = DEF_BPP;
	fps = DEF_FPS;

	background = 0;
	background = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE);
	if (!background)
		exit(1);
}

Engine::~Engine(void)
{
	if (background)
		SDL_FreeSurface(background);
	background = 0;
}

void Engine::start(void)
{
	running = true;
	while (running) {
		handle();
		render();
		delay();
	}
}

void Engine::handle(void)
{
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			running = false;
	}
}

void Engine::update(void)
{

}

void Engine::render(void)
{
	SDL_Flip(background);
}

void Engine::delay(void)
{
	SDL_Delay(1000 / fps);
}

} // namespace gs
