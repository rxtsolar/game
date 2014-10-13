#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "activity-main.h"

using namespace std;

namespace gs {

StartButton::StartButton(Activity* activity) :
	TextButton(activity, "START", this->x, this->y, this->w, this->h)
{

}

StartButton::~StartButton(void)
{

}

bool StartButton::leftClick(void)
{
	Activity* activity = getActivity();
	Engine* engine = activity->getEngine();
	engine->setCurrent(engine->getBattleActivity());
	activity->stop();
	return true;
}


ExitButton::ExitButton(Activity* activity) :
	TextButton(activity, "EXIT", this->x, this->y, this->w, this->h)
{

}

ExitButton::~ExitButton(void)
{

}

bool ExitButton::leftClick(void)
{
	Activity* activity = getActivity();
	Engine* engine = activity->getEngine();
	engine->setCurrent(0);
	activity->stop();
	return true;
}


MainActivity::MainActivity(Engine* engine, SDL_Surface* screen) : Activity(engine, screen)
{
	this->startButton = new StartButton(this);
	this->exitButton = new ExitButton(this);

}

MainActivity::~MainActivity(void)
{
	delete this->startButton;
	delete this->exitButton;

}

void MainActivity::handle(void)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			getEngine()->setCurrent(0);
			stop();
		}
		if (this->startButton->handle(&event))
			continue;
		if (this->exitButton->handle(&event))
			continue;
	}
}

void MainActivity::render(void)
{
	SDL_Surface* screen = getScreen();
	SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0xff, 0xff, 0xff));

	this->startButton->render(screen);
	this->exitButton->render(screen);

	SDL_Flip(screen);
}

} // namespace gs
