#include <iostream>

#include <SDL/SDL_ttf.h>

#include "engine.h"
#include "activity-main.h"
#include "activity-battle.h"

using namespace std;

namespace gs {

Engine::Engine(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		exit(1);

	if (TTF_Init() < 0)
		exit(1);

	this->screen = 0;
	this->screen = SDL_SetVideoMode(DEF_WIDTH, DEF_HEIGHT,
									DEF_BPP, SDL_SWSURFACE);
	if (!this->screen)
		exit(1);

	this->mainActivity = new MainActivity(this, screen);
	this->battleActivity = new BattleActivity(this, screen);

	this->game = 0;
}

Engine::~Engine(void)
{
	if (this->screen)
		SDL_FreeSurface(this->screen);
	this->screen = 0;

	delete this->mainActivity;
	delete this->battleActivity;
	if (this->game)
		delete this->game;

	TTF_Quit();
	SDL_Quit();
}

Activity* Engine::getMainActivity(void)
{
	return this->mainActivity;
}

Activity* Engine::getBattleActivity(void)
{
	return this->battleActivity;
}

Game* Engine::getGame(void)
{
	return this->game;
}

void Engine::setCurrent(Activity* activity)
{
	this->current = activity;
}

void Engine::startGame(void)
{
	this->game = new Game();
}

void Engine::endGame(void)
{
	delete this->game;
	this->game = 0;
}

void Engine::start(void)
{
	this->current = this->mainActivity;
	while (current) {
		this->current->start();
	}
}

} // namespace gs
