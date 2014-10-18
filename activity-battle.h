#ifndef _A_BATTLE_H_
#define _A_BATTLE_H_

#include <vector>
#include <iostream>

#include "activity.h"
#include "basic.h"
#include "engine.h"
#include "card-pawn.h"

using namespace std;

namespace gs {

class CardButton : public Button {
public:
	CardButton(Activity* activity, unsigned int index);
	virtual ~CardButton(void);

	virtual bool leftClick(void);

	virtual void render(SDL_Surface* screen);

private:
	static const int x = DEF_HEIGHT;
	static const int y = DEF_HEIGHT / 12;
	static const int w = (DEF_WIDTH - DEF_HEIGHT * 13 / 12) / 5 - 10;
	static const int h = DEF_HEIGHT / 4 - 10;
	const unsigned int index;
	TTF_Font* font;
};

class ResourceButton : public Button {
public:
	ResourceButton(Activity* activity);
	virtual ~ResourceButton(void);

	virtual void render(SDL_Surface* screen);
private:
	static const int x = DEF_HEIGHT;
	static const int y = DEF_HEIGHT * 2 / 3;
	static const int w = DEF_WIDTH - DEF_HEIGHT * 13 / 12;
	static const int h = DEF_HEIGHT / 12;
	TTF_Font* font;
};

class EndTurnButton : public TextButton {
public:
	EndTurnButton(Activity* activity);
	virtual ~EndTurnButton(void);

	virtual bool leftClick(void);

private:
	static const int x = DEF_HEIGHT;
	static const int y = DEF_HEIGHT * 5 / 6;
	static const int w = DEF_WIDTH / 2 - DEF_HEIGHT * 7 / 12;
	static const int h = DEF_HEIGHT / 12;
};

class ConcedeButton : public TextButton {
public:
	ConcedeButton(Activity* activity);
	virtual ~ConcedeButton(void);

	virtual bool leftClick(void);

private:
	static const int x = DEF_WIDTH / 2 + DEF_HEIGHT / 2;
	static const int y = DEF_HEIGHT * 5 / 6;
	static const int w = DEF_WIDTH / 2 - DEF_HEIGHT * 7 / 12;
	static const int h = DEF_HEIGHT / 12;
};

class TileButton : public Button {
public:
	TileButton(Activity* activity, int row, int column);
	virtual ~TileButton(void);

	virtual bool inside(void);
	virtual bool leftClick(void);

	virtual void render(SDL_Surface* screen);

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
	UnitButton(Activity* activity, unsigned int index);
	virtual ~UnitButton(void);

	virtual bool leftClick(void);

	virtual void render(SDL_Surface* screen);

private:
	static const int x = DEF_WIDTH / 8;
	static const int y = DEF_HEIGHT / 3;
	static const int w = DEF_WIDTH * 3 / 20 - 10;
	static const int h = DEF_HEIGHT / 3;
	const unsigned int index;
	TTF_Font* font;
};

class BattleActivity : public Activity {
public:
	BattleActivity(Engine* engine, SDL_Surface* screen);
	virtual ~BattleActivity(void);

	virtual void handle(void);
	virtual void render(void);
	virtual void init(void);
	virtual void quit(void);

private:
	Button* endTurnButton;
	Button* concedeButton;
	Button* resourceButton;
	vector<Button*> cardButtons;
	vector<Button*> unitButtons;
	vector<vector<Button*> > tileButtons;
};

} // namespace gs

#endif
