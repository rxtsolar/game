#ifndef _A_MAIN_H_
#define _A_MAIN_H_

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "activity.h"
#include "button.h"
#include "engine.h"

using namespace std;

namespace gs {

class StartButton : public TextButton {
public:
	StartButton(Activity* activity);
	virtual ~StartButton(void);

	virtual void leftClick(void);

private:
	static const int x = DEF_WIDTH / 8;
	static const int y = DEF_HEIGHT / 8;
	static const int w = DEF_WIDTH * 3 / 4;
	static const int h = DEF_HEIGHT / 4;
};

class ExitButton : public TextButton {
public:
	ExitButton(Activity* activity);
	virtual ~ExitButton(void);

	virtual void leftClick(void);

private:
	static const int x = DEF_WIDTH / 8;
	static const int y = DEF_HEIGHT * 5 / 8;
	static const int w = DEF_WIDTH * 3 / 4;
	static const int h = DEF_HEIGHT / 4;
};

class MainActivity : public Activity {
public:
	MainActivity(Engine* engine, SDL_Surface* screen);
	virtual ~MainActivity(void);

	virtual void handle(void);
	virtual void render(void);

private:
	Button* startButton;
	Button* exitButton;
};

} // namespace gs

#endif
