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

	virtual Activity* getMainActivity(void);
	virtual Activity* getBattleActivity(void);

	virtual void setCurrent(Activity* activity);

	virtual void start(void);

private:
	SDL_Surface* screen;
	Activity* mainActivity;
	Activity* battleActivity;
	Activity* current;
};

} // namespace gs

#endif
