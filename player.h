#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <unordered_set>

#include "game.h"
#include "unit.h"

namespace gs {

class Game;
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

	virtual bool canCreateUnit(Tile*);
	virtual bool canSelectUnit(Unit*);
	virtual bool canSelectTile(Tile*);
	virtual bool canAttack(Tile*);
	virtual bool canMoveTo(Tile*);

	virtual bool createHero(Tile*);
	virtual bool createPawn(Tile*);
	virtual bool selectUnit(Unit*);
	virtual bool selectTile(Tile*);
	virtual bool attack(Tile*);
	virtual bool moveTo(Tile*);
	virtual void endTurn(void);
	virtual void lose(void);

private:
	Game* game;
	std::unordered_set<Unit*> units;
	std::unordered_set<Tile*> tiles;
	Hero* hero;
	Unit* selectedUnit;
	Tile* selectedTile;
};

} // namespace gs

#endif
