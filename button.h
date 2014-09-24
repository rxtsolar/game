#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <SDL/SDL.h>

namespace gs {

class Button {
public:
	Button(int x, int y, int w, int h);
	virtual ~Button(void);

	virtual void handle(SDL_Event* event);
	virtual void render(SDL_Surface* screen);

	virtual void inside(void);
	virtual void outside(void);
	virtual void leftClick(void);
	virtual void rightClick(void);
private:
	SDL_Rect box;
};

} // namespace gs

#endif
