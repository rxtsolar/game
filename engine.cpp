#include <iostream>

#include "engine.h"

using namespace std;

namespace gs {

Engine::Engine(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		exit(1);

	this->screen = 0;
	this->screen = SDL_SetVideoMode(DEF_WIDTH, DEF_HEIGHT,
									DEF_BPP, SDL_SWSURFACE);
	if (!this->screen)
		exit(1);

	this->menu = new Menu(this, screen);
	this->battle = new Battle(this, screen);
}

Engine::~Engine(void)
{
	if (this->screen)
		SDL_FreeSurface(this->screen);
	this->screen = 0;

	delete this->menu;
	delete this->battle;
}

Activity* Engine::getMenu(void)
{
	return this->menu;
}

Activity* Engine::getBattle(void)
{
	return this->battle;
}

void Engine::setCurrent(Activity* activity)
{
	this->current = activity;
}

void Engine::start(void)
{
	this->current = this->menu;
	while (current) {
		this->current->start();
	}
}

} // namespace gs
