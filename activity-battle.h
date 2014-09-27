#include <vector>

#include "activity.h"
#include "basic.h"
#include "engine.h"
#include "game.h"

using namespace std;

namespace gs {

class CardButton : public Button {
public:
	CardButton(Activity* activity) :
		Button(activity, this->x, this->y, this->w, this->h)
	{

	}

	virtual ~CardButton(void)
	{

	}

private:
	static const int x = DEF_HEIGHT;
	static const int y = DEF_HEIGHT / 12;
	static const int w = DEF_WIDTH - DEF_HEIGHT * 13 / 12;
	static const int h = DEF_HEIGHT * 2 / 3;
};

class ConcedeButton : public Button {
public:
	ConcedeButton(Activity* activity) :
		Button(activity, this->x, this->y, this->w, this->h)
	{

	}

	virtual ~ConcedeButton(void)
	{

	}

	virtual void leftClick(void)
	{
		Activity* activity = getActivity();
		Engine* engine = activity->getEngine();
		engine->setCurrent(engine->getMainActivity());
		activity->stop();
	}

private:
	static const int x = DEF_HEIGHT;
	static const int y = DEF_HEIGHT * 5 / 6;
	static const int w = DEF_WIDTH - DEF_HEIGHT * 13 / 12;
	static const int h = DEF_HEIGHT / 12;
};

class TileButton : public Button {
public:
	TileButton(Activity* activity, int row, int column) :
		Button(activity, this->x + column * this->w,
				this->y + row * this->h,
				this->w, this->h),
		row(row), column(column)
	{

	}

	virtual ~TileButton(void)
	{

	}

	virtual void render(SDL_Surface* screen)
	{
		Uint32 color;
		if ((this->row + this->column) & 1)
			color = SDL_MapRGB(screen->format, 0xbf, 0xbf, 0xbf);
		else
			color = SDL_MapRGB(screen->format, 0x9f, 0x9f, 0x9f);
		SDL_FillRect(screen, this->getBox(), color);
	}

private:
	static const int x = DEF_HEIGHT / 12;
	static const int y = DEF_HEIGHT / 12;
	static const int w = DEF_HEIGHT / 6;
	static const int h = DEF_HEIGHT / 6;
	const int row;
	const int column;
};

class UnitButton : public Button {
public:
	UnitButton(Activity* activity) : Button(activity)
	{

	}

	virtual ~UnitButton(void)
	{

	}
};

class BattleActivity : public Activity {
public:
	BattleActivity(Engine* engine, SDL_Surface* screen) : Activity(engine, screen)
	{
		this->cardButton = new CardButton(this);
		this->concedeButton = new ConcedeButton(this);
		this->unitButton = new UnitButton(this);
		this->tileButtons.resize(BOARD_WIDTH, vector<Button*>(BOARD_HEIGHT));
		for (unsigned int i = 0; i < BOARD_WIDTH; i++)
			for (unsigned int j = 0; j < BOARD_HEIGHT; j++)
				this->tileButtons[i][j] = new TileButton(this, i, j);
	}

	virtual ~BattleActivity(void)
	{
		delete this->cardButton;
		delete this->concedeButton;
		delete this->unitButton;
		for (unsigned int i = 0; i < BOARD_WIDTH; i++)
			for (unsigned int j = 0; j < BOARD_HEIGHT; j++)
				delete this->tileButtons[i][j];
		if (this->game)
			delete this->game;
	}

	virtual void handle(void)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				stop();
			this->concedeButton->handle(&event);
		}
	}

	virtual void render(void)
	{
		SDL_Surface* screen = getScreen();
		SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0xff, 0x00, 0x00));

		this->cardButton->render(screen);
		this->concedeButton->render(screen);
		for (unsigned int i = 0; i < BOARD_WIDTH; i++)
			for (unsigned int j = 0; j < BOARD_HEIGHT; j++)
				this->tileButtons[i][j]->render(screen);
		this->unitButton->render(screen);

		SDL_Flip(screen);
	}

	virtual void init(void)
	{
		this->game = new Game();
	}

	virtual void quit(void)
	{
		delete this->game;
		this->game = 0;
	}

	virtual void setStatus(Status status)
	{
		this->cardButton->setStatus(status);
		this->concedeButton->setStatus(status);
		this->unitButton->setStatus(status);
		for (unsigned int i = 0; i < BOARD_WIDTH; i++)
			for (unsigned int j = 0; j < BOARD_HEIGHT; j++)
				this->tileButtons[i][j]->setStatus(status);
	}

private:
	Button* cardButton;
	Button* concedeButton;
	Button* unitButton;
	vector<vector<Button*> > tileButtons;
	Game* game;
};

} // namespace gs
