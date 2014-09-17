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
	while (this->running) {
		handle();
		render();
		delay();
	}
}

void Activity::stop(void)
{
	this->running = false;
}


Menu::Menu(Engine* engine, SDL_Surface* screen) : Activity(engine, screen)
{

}

Menu::~Menu(void)
{

}

void Menu::handle(void)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			stop();

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				getEngine()->setCurrent(getEngine()->getBattle());
				stop();
			}
			if (event.button.button == SDL_BUTTON_RIGHT) {
				getEngine()->setCurrent(0);
				stop();
			}
		}
	}
}

void Menu::update(void)
{

}

void Menu::render(void)
{
	SDL_Surface* screen = getScreen();
	SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0xff, 0xff, 0xff));
	SDL_Flip(screen);
}

void Menu::delay(void)
{
	SDL_Delay(1000 / DEF_FPS);
}


Battle::Battle(Engine* engine, SDL_Surface* screen) : Activity(engine, screen)
{

}

Battle::~Battle(void)
{

}

void Battle::handle(void)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			stop();

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				getEngine()->setCurrent(getEngine()->getMenu());
				stop();
			}
		}
	}
}

void Battle::update(void)
{

}

void Battle::render(void)
{
	SDL_Surface* screen = getScreen();
	SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0xff, 0x00, 0x00));
	SDL_Flip(screen);
}

void Battle::delay(void)
{
	SDL_Delay(1000 / DEF_FPS);
}

} // namespace gs
