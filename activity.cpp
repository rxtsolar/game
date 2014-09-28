#include "activity.h"

namespace gs {

Activity::Activity(Engine* engine, SDL_Surface* screen)
{
	this->engine = engine;
	this->screen = screen;
	this->running = false;
}

Activity::~Activity(void)
{

}

Engine* Activity::getEngine(void)
{
	return this->engine;
}

SDL_Surface* Activity::getScreen(void)
{
	return this->screen;
}

void Activity::start(void)
{
	this->running = true;
	init();
	while (this->running) {
		handle();
		render();
		delay();
	}
	quit();
}

void Activity::stop(void)
{
	this->running = false;
}

void Activity::handle(void)
{

}

void Activity::update(void)
{

}

void Activity::render(void)
{

}

void Activity::init(void)
{

}

void Activity::quit(void)
{

}

void Activity::delay(void)
{
	SDL_Delay(1000 / DEF_FPS);
}

void Activity::setStatus(Status status)
{

}

} // namespace gs
