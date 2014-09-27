#include <vector>

#include "activity.h"
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

class BattleActivity : public Activity {
public:
	BattleActivity(Engine* engine, SDL_Surface* screen) : Activity(engine, screen)
	{
		this->cardButton = new CardButton(this);
		this->concedeButton = new ConcedeButton(this);
		this->tileButtons.resize(BOARD_WIDTH, vector<Button*>(BOARD_HEIGHT));
		for (unsigned int i = 0; i < BOARD_WIDTH; i++)
			for (unsigned int j = 0; j < BOARD_HEIGHT; j++)
				this->tileButtons[i][j] = new TileButton(this, i, j);
	}

	virtual ~BattleActivity(void)
	{
		delete this->cardButton;
		delete this->concedeButton;
		for (unsigned int i = 0; i < BOARD_WIDTH; i++)
			for (unsigned int j = 0; j < BOARD_HEIGHT; j++)
				delete this->tileButtons[i][j];
	}

	virtual void handle(void)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				stop();

			if (event.type == SDL_MOUSEBUTTONDOWN) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					getEngine()->setCurrent(getEngine()->getMainActivity());
					stop();
				}
			}
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

		SDL_Flip(screen);
	}
private:
	Button* cardButton;
	Button* concedeButton;
	vector<vector<Button*> > tileButtons;
};

} // namespace gs