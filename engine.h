#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SDL/SDL.h>

#include "activity.h"

namespace gs {

const int DEF_WIDTH = 1280;
const int DEF_HEIGHT = 720;
const int DEF_BPP = 32;

class Activity;

class Engine {
public:
	Engine(void);
	virtual ~Engine(void);

	virtual Activity* getMenu(void);
	virtual Activity* getBattle(void);

	virtual void setCurrent(Activity* activity);

	virtual void start(void);

private:
	SDL_Surface* screen;
	Activity* menu;
	Activity* battle;
	Activity* current;
};

} // namespace gs

#endif