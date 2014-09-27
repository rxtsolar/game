#include "activity.h"
#include "button.h"
#include "engine.h"

namespace gs {

class StartButton : public Button {
public:
	StartButton(Activity* activity) :
		Button(activity, this->x, this->y, this->w, this->h)
	{

	}

	virtual ~StartButton(void)
	{

	}

	virtual void leftClick(void)
	{
		Activity* activity = getActivity();
		Engine* engine = activity->getEngine();
		engine->setCurrent(engine->getBattleActivity());
		activity->stop();
	}

private:
	static const int x = DEF_WIDTH / 8;
	static const int y = DEF_HEIGHT / 8;
	static const int w = DEF_WIDTH * 3 / 4;
	static const int h = DEF_HEIGHT / 4;
};

class ExitButton : public Button {
public:
	ExitButton(Activity* activity) :
		Button(activity, this->x, this->y, this->w, this->h)
	{

	}

	virtual ~ExitButton(void)
	{

	}

	virtual void leftClick(void)
	{
		Activity* activity = getActivity();
		Engine* engine = activity->getEngine();
		engine->setCurrent(0);
		activity->stop();
	}

private:
	static const int x = DEF_WIDTH / 8;
	static const int y = DEF_HEIGHT * 5 / 8;
	static const int w = DEF_WIDTH * 3 / 4;
	static const int h = DEF_HEIGHT / 4;
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