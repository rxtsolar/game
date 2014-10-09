#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <unordered_set>

#include "card.h"
#include "game.h"
#include "unit.h"

namespace gs {

class Game;
class Card;
class Unit;
class Tile;
class Hero;

class Player {
public:
	Player(Game* game);
	virtual ~Player(void);

	virtual void addUnit(Unit*);
	virtual void removeUnit(Unit*);
	virtual void addTile(Tile*);
	virtual void removeTile(Tile*);

	virtual Game* getGame(void);
	virtual std::unordered_set<Unit*> getUnits(void);
	virtual std::unordered_set<Tile*> getTiles(void);
	virtual Hero* getHero(void);
	virtual Unit* getSelectedUnit(void);
	virtual Tile* getSelectedTile(void);
	virtual int getResources(void);
	virtual int getMaxResources(void);

	virtual bool canSelectUnit(Unit*);
	virtual bool canSelectTile(Tile*);
	virtual bool canSelectCard(Card*);
	virtual bool canPlayCard(Tile*);
	virtual bool canAttack(Tile*);
	virtual bool canMoveTo(Tile*);

	virtual bool createHero(Tile*);
	virtual bool selectUnit(Unit*);
	virtual bool selectTile(Tile*);
	virtual bool selectCard(Card*);
	virtual bool playCard(Tile*);
	virtual bool attack(Tile*);
	virtual bool moveTo(Tile*);
	virtual void increaseResources(int);
	virtual void decreaseResources(int);
	virtual void increaseMaxResources(int);
	virtual void decreaseMaxResources(int);
	virtual void fillResources(void);
	virtual void startTurn(void);
	virtual void endTurn(void);
	virtual void lose(void);

private:
	Game* game;
	std::unordered_set<Unit*> units;
	std::unordered_set<Tile*> tiles;
	Hero* hero;
	Unit* selectedUnit;
	Tile* selectedTile;
	Card* selectedCard;
	int resources;
	int maxResources;
};

} // namespace gs

#endif
