#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SDL/SDL.h>

#include "activity.h"
#include "const.h"
#include "game.h"

namespace gs {

class Activity;

class Engine {
public:
	Engine(void);
	virtual ~Engine(void);

	virtual Activity* getMainActivity(void);
	virtual Activity* getBattleActivity(void);
	virtual Game* getGame(void);

	virtual void setCurrent(Activity* activity);

	virtual void startGame(void);
	virtual void endGame(void);

	virtual void start(void);

private:
	SDL_Surface* screen;
	Activity* mainActivity;
	Activity* battleActivity;
	Activity* current;
	Game* game;
};

} // namespace gs

#endif
