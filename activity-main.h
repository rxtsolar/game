#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "activity.h"
#include "button.h"
#include "engine.h"

using namespace std;

namespace gs {

const char* font_path = "resources/black_jack.ttf";
const float font_rate = 0.656;

class StartButton : public Button {
public:
	StartButton(Activity* activity) :
		Button(activity, this->x, this->y, this->w, this->h)
	{
		this->font = TTF_OpenFont(font_path, this->h * font_rate);
	}

	virtual ~StartButton(void)
	{
		if (this->font)
			TTF_CloseFont(this->font);
	}

	virtual void leftClick(void)
	{
		Activity* activity = getActivity();
		Engine* engine = activity->getEngine();
		engine->setCurrent(engine->getBattleActivity());
		activity->stop();
	}

	virtual void render(SDL_Surface* screen)
	{
		SDL_Color color = { 0x0f, 0x0f, 0x0f };
		SDL_Rect offset;
		SDL_Surface* message = TTF_RenderText_Blended(this->font, text, color);

		SDL_FillRect(screen, this->getBox(),
				SDL_MapRGB(screen->format, 0xaf, 0xaf, 0xaf));
		offset.x = this->x + (this->w - message->w) / 2;
		offset.y = this->y + (this->h - message->h) / 2;
		SDL_BlitSurface(message, 0, screen, &offset);

		SDL_FreeSurface(message);
	}

private:
	static const int x = DEF_WIDTH / 8;
	static const int y = DEF_HEIGHT / 8;
	static const int w = DEF_WIDTH * 3 / 4;
	static const int h = DEF_HEIGHT / 4;
	static constexpr const char* text = "START";
	TTF_Font* font;
};

class ExitButton : public Button {
public:
	ExitButton(Activity* activity) :
		Button(activity, this->x, this->y, this->w, this->h)
	{
		this->font = TTF_OpenFont(font_path, this->h * font_rate);
	}

	virtual ~ExitButton(void)
	{
		if (this->font)
			TTF_CloseFont(this->font);
	}

	virtual void leftClick(void)
	{
		Activity* activity = getActivity();
		Engine* engine = activity->getEngine();
		engine->setCurrent(0);
		activity->stop();
	}

	virtual void render(SDL_Surface* screen)
	{
		SDL_Color color = { 0x0f, 0x0f, 0x0f };
		SDL_Rect offset;
		SDL_Surface* message = TTF_RenderText_Blended(this->font, text, color);

		SDL_FillRect(screen, this->getBox(),
				SDL_MapRGB(screen->format, 0xaf, 0xaf, 0xaf));
		offset.x = this->x + (this->w - message->w) / 2;
		offset.y = this->y + (this->h - message->h) / 2;
		SDL_BlitSurface(message, 0, screen, &offset);

		SDL_FreeSurface(message);
	}

private:
	static const int x = DEF_WIDTH / 8;
	static const int y = DEF_HEIGHT * 5 / 8;
	static const int w = DEF_WIDTH * 3 / 4;
	static const int h = DEF_HEIGHT / 4;
	static constexpr const char* text = "EXIT";
	TTF_Font* font;
};

class MainActivity : public Activity {
public:
	MainActivity(Engine* engine, SDL_Surface* screen) : Activity(engine, screen)
	{
		this->startButton = new StartButton(this);
		this->exitButton = new ExitButton(this);

	}

	virtual ~MainActivity(void)
	{
		delete this->startButton;
		delete this->exitButton;

	}

	virtual void handle(void)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				stop();
			this->startButton->handle(&event);
			this->exitButton->handle(&event);
		}
	}

	virtual void render(void)
	{
		SDL_Surface* screen = getScreen();
		SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0xff, 0xff, 0xff));

		this->startButton->render(screen);
		this->exitButton->render(screen);

		SDL_Flip(screen);
	}
private:
	Button* startButton;
	Button* exitButton;
};

} // namespace gs
