#ifndef _ACTIVITY_H_
#define _ACTIVITY_H_

#include <SDL/SDL.h>

#include "button.h"
#include "const.h"
#include "engine.h"

namespace gs {

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
	virtual void init(void);
	virtual void quit(void);
	virtual void delay(void);

	virtual void setStatus(Status status);

private:
	bool running;
	Engine* engine;
	SDL_Surface* screen;
};

} // namespace gs

#endif
