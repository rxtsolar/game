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
	CardButton(Activity* activity);
	virtual ~CardButton(void);

	virtual void leftClick(void);

	virtual void render(SDL_Surface* screen);

private:
	static const int x = DEF_HEIGHT;
	static const int y = DEF_HEIGHT / 12;
	static const int w = DEF_WIDTH - DEF_HEIGHT * 13 / 12;
	static const int h = DEF_HEIGHT * 2 / 3;
};

class EndTurnButton : public TextButton {
public:
	EndTurnButton(Activity* activity);
	virtual ~EndTurnButton(void);

	virtual void leftClick(void);

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

	virtual void leftClick(void);

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

	virtual void leftClick(void);

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
	UnitButton(Activity* activity);
	virtual ~UnitButton(void);
};

class BattleActivity : public Activity {
public:
	BattleActivity(Engine* engine, SDL_Surface* screen);
	virtual ~BattleActivity(void);

	virtual void handle(void);
	virtual void render(void);
	virtual void init(void);
	virtual void quit(void);

	virtual void setStatus(Status status);

private:
	Button* cardButton;
	Button* endTurnButton;
	Button* concedeButton;
	Button* unitButton;
	vector<vector<Button*> > tileButtons;
};

} // namespace gs

#endif
