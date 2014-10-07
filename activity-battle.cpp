#include <vector>
#include <iostream>

#include "activity-battle.h"

using namespace std;

namespace gs {

CardButton::CardButton(Activity* activity) :
	TextButton(activity, "A", this->x, this->y, this->w, this->h)
{

}

CardButton::~CardButton(void)
{

}

bool CardButton::leftClick(void)
{
	bool handled = false;

	switch (getStatus()) {
	case S_DEFAULT:
		getActivity()->setStatus(S_CARD);
		handled = true;
		break;
	default:
		break;
	}

	return handled;
}

void CardButton::render(SDL_Surface* screen)
{
	Uint32 color;

	TextButton::render(screen);
	switch (getStatus()) {
	case S_CARD:
	{
		color = SDL_MapRGB(screen->format, 0x6f, 0xff, 0xff);
		SDL_FillRect(screen, this->getBox(), color);
		break;
	}
	default:
		break;
	}
}


EndTurnButton::EndTurnButton(Activity* activity) :
	TextButton(activity, "End Turn", this->x, this->y, this->w, this->h)
{

}

EndTurnButton::~EndTurnButton(void)
{

}

bool EndTurnButton::leftClick(void)
{
	bool handled = false;

	switch (getStatus()) {
	case S_DEFAULT:
	{
		Game* game = getActivity()->getEngine()->getGame();
		game->getTurn()->endTurn();
		handled = true;
		break;
	}
	default:
		break;
	}

	return handled;
}


ConcedeButton::ConcedeButton(Activity* activity) :
	TextButton(activity, "Concede", this->x, this->y, this->w, this->h)
{

}

ConcedeButton::~ConcedeButton(void)
{

}

bool ConcedeButton::leftClick(void)
{
	bool handled = false;

	switch (getStatus()) {
	case S_DEFAULT:
	{
		Activity* activity = getActivity();
		Engine* engine = activity->getEngine();
		engine->setCurrent(engine->getMainActivity());
		activity->stop();
		handled = true;
		break;
	}
	default:
		break;
	}

	return handled;
}


TileButton::TileButton(Activity* activity, int row, int column) :
	Button(activity, this->x + column * this->w,
			this->y + row * this->h,
			this->w, this->h),
	row(row), column(column)
{
	this->font = TTF_OpenFont(font_path, this->h * font_rate);
}

TileButton::~TileButton(void)
{
	if (this->font)
		TTF_CloseFont(this->font);
}

bool TileButton::leftClick(void)
{
	bool handled = false;
	Game* game = getActivity()->getEngine()->getGame();
	Tile* tile = game->getBoard()->getTile(Position(this->row, this->column));

	switch (getStatus()) {
	case S_DEFAULT:
	{
		if (game->getTurn()->selectTile(tile)) {
			getActivity()->setStatus(S_TILE);
			handled = true;
		}
		break;
	}
	case S_CARD:
	{
		if (game->getTurn()->createPawn(tile)) {
			getActivity()->setStatus(S_DEFAULT);
			handled = true;
		}
		break;
	}
	case S_UNIT:
	{
		if (game->getTurn()->canAttack(tile)) {
			game->getTurn()->attack(tile);
			getActivity()->setStatus(S_DEFAULT);
			handled = true;
		} else if (game->getTurn()->canMoveTo(tile)) {
			game->getTurn()->moveTo(tile);
			getActivity()->setStatus(S_DEFAULT);
			handled = true;
		}
		break;
	}
	default:
		break;
	}

	return handled;
}

void TileButton::render(SDL_Surface* screen)
{
	Game* game = getActivity()->getEngine()->getGame();
	Tile* tile = game->getBoard()->getTile(Position(this->row, this->column));
	string n = to_string(tile->getSize());
	SDL_Color fontColor = { 0x0f, 0x0f, 0x0f };
	SDL_Surface* message = TTF_RenderText_Blended(this->font, n.c_str(), fontColor);
	Uint32 color;
	bool handled = false;

	SDL_Rect offset = {
		(Sint16)(this->x + column * this->w),
		(Sint16)(this->y + row * this->h),
	};

	switch (getStatus()) {
	case S_UNIT:
	{
		handled = true;
		if (game->getTurn()->getSelectedTile() == tile)
			color = SDL_MapRGB(screen->format, 0x6f, 0xff, 0xff);
		else if (game->getTurn()->getSelectedUnit()->canMoveTo(tile))
			color = SDL_MapRGB(screen->format, 0xff, 0xff, 0x6f);
		else if (game->getTurn()->getSelectedUnit()->canAttack(tile))
			color = SDL_MapRGB(screen->format, 0xff, 0x6f, 0xff);
		else
			handled = false;
	}
	case S_TILE:
	case S_CARD:
	case S_DEFAULT:
	{
		if (handled)
			break;
		if (tile->getPlayer() == game->getPlayer1())
			color = SDL_MapRGB(screen->format, 0xff, 0x6f, 0x6f);
		else if (tile->getPlayer() == game->getPlayer2())
			color = SDL_MapRGB(screen->format, 0x6f, 0x6f, 0xff);
		else if ((this->row + this->column) & 1)
			color = SDL_MapRGB(screen->format, 0xbf, 0xbf, 0xbf);
		else
			color = SDL_MapRGB(screen->format, 0x9f, 0x9f, 0x9f);
		break;
	}
	default:
		break;
	}

	SDL_FillRect(screen, this->getBox(), color);
	SDL_BlitSurface(message, 0, screen, &offset);

	SDL_FreeSurface(message);
}


UnitButton::UnitButton(Activity* activity, unsigned int index) :
	Button(activity, this->x + index * (this->w + 10),
			this->y, this->w, this->h),
	index(index)
{
	this->font = TTF_OpenFont(font_path, this->h / 6 * font_rate);
}

UnitButton::~UnitButton(void)
{
	if (this->font)
		TTF_CloseFont(this->font);
}

bool UnitButton::leftClick(void)
{
	bool handled = false;

	switch (getStatus()) {
	case S_TILE:
	{
		Game* game = getActivity()->getEngine()->getGame();
		Tile* tile = game->getTurn()->getSelectedTile();

		if (this->index < tile->getSize()) {
			Unit* unit = tile->getUnit(this->index);

			if (!unit->isAttacked() && unit->getDamage() > 0) {
				game->getTurn()->selectUnit(unit);
				getActivity()->setStatus(S_UNIT);
				handled = true;
			}
		}
		break;
	}
	default:
		break;
	}

	return handled;
}

void UnitButton::render(SDL_Surface* screen)
{
	switch (getStatus()) {
	case S_TILE:
	{
		Game* game = getActivity()->getEngine()->getGame();
		Tile* tile = game->getTurn()->getSelectedTile();

		if (this->index < tile->getSize()) {
			Unit* unit = tile->getUnit(this->index);
			string damage = to_string(unit->getDamage());
			string life = to_string(unit->getLife());
			SDL_Color fontColor = { 0xff, 0xff, 0xff };
			SDL_Surface* d = TTF_RenderText_Blended(this->font,
					damage.c_str(), fontColor);
			SDL_Surface* l = TTF_RenderText_Blended(this->font,
					life.c_str(), fontColor);
			Uint32 color = SDL_MapRGB(screen->format, 0x3f, 0x3f, 0x3f);
			SDL_Rect offset;

			SDL_FillRect(screen, this->getBox(), color);
			offset.y = (Sint16)(this->y + this->h * 5 / 6);
			offset.x = (Sint16)this->x + index * (this->w + 10);
			SDL_BlitSurface(d, 0, screen, &offset);
			offset.x = (Sint16)this->x + this->w * 3 / 4 + index * (this->w + 10);
			SDL_BlitSurface(l, 0, screen, &offset);

			SDL_FreeSurface(d);
			SDL_FreeSurface(l);
		}
		break;
	}
	default:
		break;
	}
}


BattleActivity::BattleActivity(Engine* engine, SDL_Surface* screen) :
	Activity(engine, screen)
{
	this->cardButton = new CardButton(this);
	this->endTurnButton = new EndTurnButton(this);
	this->concedeButton = new ConcedeButton(this);
	this->unitButtons.resize(TILE_LIMIT);
	for (unsigned int i = 0; i < TILE_LIMIT; i++)
		this->unitButtons[i] = new UnitButton(this, i);
	this->tileButtons.resize(BOARD_WIDTH, vector<Button*>(BOARD_HEIGHT));
	for (unsigned int i = 0; i < BOARD_WIDTH; i++)
		for (unsigned int j = 0; j < BOARD_HEIGHT; j++)
			this->tileButtons[i][j] = new TileButton(this, i, j);
}

BattleActivity::~BattleActivity(void)
{
	delete this->cardButton;
	delete this->endTurnButton;
	delete this->concedeButton;
	for (unsigned int i = 0; i < TILE_LIMIT; i++)
		delete this->unitButtons[i];
	for (unsigned int i = 0; i < BOARD_WIDTH; i++)
		for (unsigned int j = 0; j < BOARD_HEIGHT; j++)
			delete this->tileButtons[i][j];
}

void BattleActivity::handle(void)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		bool handled = false;

		if (event.type == SDL_QUIT)
			stop();

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				if (getEngine()->getGame()->isFinished()) {
					getEngine()->setCurrent(getEngine()->getMainActivity());
					stop();
					break;
				}
			}
		}

		if (this->cardButton->handle(&event))
			continue;
		if (this->endTurnButton->handle(&event))
			continue;
		if (this->concedeButton->handle(&event))
			continue;
		for (unsigned int i = 0; i < BOARD_WIDTH; i++)
			for (unsigned int j = 0; j < BOARD_HEIGHT; j++)
				if (this->tileButtons[i][j]->handle(&event))
					handled = true;
		if (handled)
			continue;
		for (unsigned int i = 0; i < TILE_LIMIT; i++)
			if (this->unitButtons[i]->handle(&event))
				handled = true;
		if (handled)
			continue;

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_RIGHT) {
				Game* game = getEngine()->getGame();
				game->getTurn()->selectTile(0);
				game->getTurn()->selectUnit(0);
				setStatus(S_DEFAULT);
			}
		}
	}
}

void BattleActivity::render(void)
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
	for (unsigned int i = 0; i < TILE_LIMIT; i++)
		this->unitButtons[i]->render(screen);

	SDL_Flip(screen);
}

void BattleActivity::init(void)
{
	getEngine()->startGame();
}

void BattleActivity::quit(void)
{
	getEngine()->endGame();
}

void BattleActivity::setStatus(Status status)
{
	this->cardButton->setStatus(status);
	this->endTurnButton->setStatus(status);
	this->concedeButton->setStatus(status);
	for (unsigned int i = 0; i < TILE_LIMIT; i++)
		this->unitButtons[i]->setStatus(status);
	for (unsigned int i = 0; i < BOARD_WIDTH; i++)
		for (unsigned int j = 0; j < BOARD_HEIGHT; j++)
			this->tileButtons[i][j]->setStatus(status);
}

} // namespace gs
