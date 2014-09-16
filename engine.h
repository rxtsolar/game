#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <SDL/SDL.h>

namespace gs {

const int DEF_WIDTH = 1280;
const int DEF_HEIGHT = 720;
const int DEF_BPP = 32;
const int DEF_FPS = 25;

class Engine {
public:
	Engine(void);
	virtual ~Engine(void);

	virtual void start(void);

private:
	int width;
	int height;
	int bpp;
	int fps;
	bool running;
	SDL_Event event;
	SDL_Surface* background;

	virtual void handle(void);
	virtual void update(void);
	virtual void render(void);
	virtual void delay(void);
};

} // namespace gs

#endif
