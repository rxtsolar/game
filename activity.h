#ifndef _ACTIVITY_H_
#define _ACTIVITY_H_

#include <SDL/SDL.h>

#include "engine.h"

namespace gs {

const int DEF_FPS = 25;

class Engine;

class Activity {
public:
	Activity(Engine* engine, SDL_Surface* screen);
	virtual ~Activity(void);

	virtual Engine* getEngine(void);
	virtual SDL_Surface* getScreen(void);

	virtual void start(void);
	virtual void stop(void);

	virtual void handle(void) = 0;
	virtual void update(void) = 0;
	virtual void render(void) = 0;
	virtual void delay(void) = 0;

private:
	bool running;
	Engine* engine;
	SDL_Surface* screen;
};

class Menu : public Activity {
public:
	Menu(Engine* engine, SDL_Surface* screen);
	virtual ~Menu(void);

	virtual void handle(void);
	virtual void update(void);
	virtual void render(void);
	virtual void delay(void);
};

class Battle : public Activity {
public:
	Battle(Engine* engine, SDL_Surface* screen);
	virtual ~Battle(void);

	virtual void handle(void);
	virtual void update(void);
	virtual void render(void);
	virtual void delay(void);
};

} // namespace gs

#endif
