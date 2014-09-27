#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SDL/SDL.h>

#include "activity.h"
#include "const.h"

namespace gs {

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
