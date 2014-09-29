#ifndef _A_BATTLE_H_
#define _A_BATTLE_H_

#include <vector>
#include <iostream>

#include "activity.h"
#include "basic.h"
#include "engine.h"

using namespace std;

namespace gs {

class CardButton : public TextButton {
public:
	CardButton(Activity* activity) :
		TextButton(activity, "A", this->x, this->y, this->w, this->h)
	{

	}

	virtual ~CardButton(void)
	{

	}

	virtual void leftClick(void)
	{
		cerr << getStatus() << endl;
		switch (getStatus()) {
		case S_DEFAULT:
			getActivity()->setStatus(S_CARD);
			break;
		default:
			break;
		}
	}

	virtual void render(SDL_Surface* screen)
	{
		Uint32 color;

		TextButton::render(screen);
		switch (getStatus()) {
		case S_CARD:
		{
			color = SDL_MapRGBA(screen->format, 0x6f, 0xff, 0xff, 0xaf);
			SDL_FillRect(screen, this->getBox(), color);
			break;
		}
		default:
			break;
		}
	}

private:
	static const int x = DEF_HEIGHT;
	static const int y = DEF_HEIGHT / 12;
	static const int w = DEF_WIDTH - DEF_HEIGHT * 13 / 12;
	static const int h = DEF_HEIGHT * 2 / 3;
};

class EndTurnButton : public TextButton {
public:
	EndTurnButton(Activity* activity) :
		TextButton(activity, "End Turn", this->x, this->y, this->w, this->h)
	{

	}

	virtual ~EndTurnButton(void)
	{

	}

	virtual void leftClick(void)
	{
		switch (getStatus()) {
		case S_DEFAULT:
		{
			Game* game = getActivity()->getEngine()->getGame();
			game->getTurn()->endTurn();
			break;
		}
		default:
			break;
		}
	}

private:
	static const int x = DEF_HEIGHT;
	static const int y = DEF_HEIGHT * 5 / 6;
	static const int w = DEF_WIDTH / 2 - DEF_HEIGHT * 7 / 12;
	static const int h = DEF_HEIGHT / 12;
};

class ConcedeButton : public TextButton {
public:
	ConcedeButton(Activity* activity) :
		TextButton(activity, "Concede", this->x, this->y, this->w, this->h)
	{

	}

	virtual ~ConcedeButton(void)
	{

	}

	virtual void leftClick(void)
	{
		switch (getStatus()) {
		case S_DEFAULT:
		{
			Activity* activity = getActivity();
			Engine* engine = activity->getEngine();
			engine->setCurrent(engine->getMainActivity());
			activity->stop();
			break;
		}
		default:
			break;
		}
	}

private:
	static const int x = DEF_WIDTH / 2 + DEF_HEIGHT / 2;
	static const int y = DEF_HEIGHT * 5 / 6;
	static const int w = DEF_WIDTH / 2 - DEF_HEIGHT * 7 / 12;
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
		this->font = TTF_OpenFont(font_path, this->h * font_rate);
	}

	virtual ~TileButton(void)
	{
		if (this->font)
			TTF_CloseFont(this->font);
	}

	virtual void leftClick(void)
	{
		switch (getStatus()) {
		case S_DEFAULT:
			break;
		case S_CARD:
		{
			Game* game = getActivity()->getEngine()->getGame();
			Tile* tile = game->getBoard()->getTile(Position(this->row, this->column));
			game->getTurn()->createPawn(tile);
			getActivity()->setStatus(S_DEFAULT);
			break;
		}
		default:
			break;
		}
	}

	virtual void render(SDL_Surface* screen)
	{
		Game* game = getActivity()->getEngine()->getGame();
		Tile* tile = game->getBoard()->getTile(Position(this->row, this->column));
		string n = to_string(tile->getSize());
		SDL_Color fontColor = { 0x0f, 0x0f, 0x0f };
		SDL_Surface* message = TTF_RenderText_Blended(this->font, n.c_str(), fontColor);
		Uint32 color;
		SDL_Rect offset = {
			(Sint16)(this->x + column * this->w),
			(Sint16)(this->y + row * this->h),
		};

		if (tile->getPlayer() == game->getPlayer1())
			color = SDL_MapRGB(screen->format, 0xff, 0x6f, 0x6f);
		else if (tile->getPlayer() == game->getPlayer2())
			color = SDL_MapRGB(screen->format, 0x6f, 0x6f, 0xff);
		else if ((this->row + this->column) & 1)
			color = SDL_MapRGB(screen->format, 0xbf, 0xbf, 0xbf);
		else
			color = SDL_MapRGB(screen->format, 0x9f, 0x9f, 0x9f);
		SDL_FillRect(screen, this->getBox(), color);
		SDL_BlitSurface(message, 0, screen, &offset);

		SDL_FreeSurface(message);
	}

private:
	static const int x = DEF_HEIGHT / 12;
	static const int y = DEF_HEIGHT / 12;
	static const int w = DEF_HEIGHT / 6;
	static const int h = DEF_HEIGHT / 6;
	const int row;
	const int column;
	TTF_Font* font;
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
	BattleActivity(Engine* engine, SDL_Surface* screen) :
		Activity(engine, screen)
	{
		this->cardButton = new CardButton(this);
		this->endTurnButton = new EndTurnButton(this);
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
		delete this->endTurnButton;
		delete this->concedeButton;
		delete this->unitButton;
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

			this->cardButton->handle(&event);
			this->endTurnButton->handle(&event);
			this->concedeButton->handle(&event);
			for (unsigned int i = 0; i < BOARD_WIDTH; i++)
				for (unsigned int j = 0; j < BOARD_HEIGHT; j++)
					this->tileButtons[i][j]->handle(&event);
			this->unitButton->handle(&event);

			if (event.type == SDL_MOUSEBUTTONDOWN)
				if (event.button.button == SDL_BUTTON_RIGHT)
					setStatus(S_DEFAULT);
		}
	}

	virtual void render(void)
	{
		SDL_Surface* screen = getScreen();
		Game* game = getEngine()->getGame();

		if (game->getTurn() == game->getPlayer1())
			SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0xff, 0x00, 0x00));
		else
			SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0x00, 0x00, 0xff));

		this->cardButton->render(screen);
		this->endTurnButton->render(screen);
		this->concedeButton->render(screen);
		for (unsigned int i = 0; i < BOARD_WIDTH; i++)
			for (unsigned int j = 0; j < BOARD_HEIGHT; j++)
				this->tileButtons[i][j]->render(screen);
		this->unitButton->render(screen);

		SDL_Flip(screen);
	}

	virtual void init(void)
	{
		getEngine()->startGame();
	}

	virtual void quit(void)
	{
		getEngine()->endGame();
	}

	virtual void setStatus(Status status)
	{
		this->cardButton->setStatus(status);
		this->endTurnButton->setStatus(status);
		this->concedeButton->setStatus(status);
		this->unitButton->setStatus(status);
		for (unsigned int i = 0; i < BOARD_WIDTH; i++)
			for (unsigned int j = 0; j < BOARD_HEIGHT; j++)
				this->tileButtons[i][j]->setStatus(status);
	}

private:
	Button* cardButton;
	Button* endTurnButton;
	Button* concedeButton;
	Button* unitButton;
	vector<vector<Button*> > tileButtons;
};

} // namespace gs

#endif
