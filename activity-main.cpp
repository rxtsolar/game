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

void StartButton::leftClick(void)
{
	Activity* activity = getActivity();
	Engine* engine = activity->getEngine();
	engine->setCurrent(engine->getBattleActivity());
	activity->stop();
}


ExitButton::ExitButton(Activity* activity) :
	TextButton(activity, "EXIT", this->x, this->y, this->w, this->h)
{

}

ExitButton::~ExitButton(void)
{

}

void ExitButton::leftClick(void)
{
	Activity* activity = getActivity();
	Engine* engine = activity->getEngine();
	engine->setCurrent(0);
	activity->stop();
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
		if (event.type == SDL_QUIT)
			stop();
		this->startButton->handle(&event);
		this->exitButton->handle(&event);
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
