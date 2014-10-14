#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "activity.h"
#include "basic.h"

namespace gs {

class Activity;

class Button {
public:
	Button(Activity* activity);
	Button(Activity* activity, int x, int y, int w, int h);
	virtual ~Button(void);

	virtual SDL_Rect* getBox(void);
	virtual Activity* getActivity(void);

	virtual void setBox(int x, int y, int w, int h);

	virtual bool handle(SDL_Event* event);
	virtual void render(SDL_Surface* screen);

	virtual bool inside(void);
	virtual bool outside(void);
	virtual bool leftClick(void);
	virtual bool rightClick(void);
private:
	SDL_Rect* box;
	Activity* activity;
};

class TextButton : public Button {
public:
	TextButton(Activity* activity, const char* text, int x, int y, int w, int h);
	virtual ~TextButton(void);

	virtual void render(SDL_Surface* screen);
private:
	TTF_Font* font;
	const char* text;
};

} // namespace gs

#endif
