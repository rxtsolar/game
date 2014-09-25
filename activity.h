#ifndef _ACTIVITY_H_
#define _ACTIVITY_H_

#include <SDL/SDL.h>

#include "engine.h"
#include "button.h"

namespace gs {

const int DEF_FPS = 25;

class Engine;
class Button;

class Activity {
public:
	Activity(Engine* engine, SDL_Surface* screen);
	virtual ~Activity(void);

	virtual Engine* getEngine(void);
	virtual SDL_Surface* getScreen(void);

	virtual void start(void);
	virtual void stop(void);

	virtual void handle(void);
	virtual void update(void);
	virtual void render(void);
	virtual void delay(void);

private:
	bool running;
	Engine* engine;
	SDL_Surface* screen;
};

} // namespace gs

#endif
