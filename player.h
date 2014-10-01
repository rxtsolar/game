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

	virtual bool canCreateUnit(Tile*);
	virtual bool canSelectUnit(Tile*, unsigned int i);

	virtual void createHero(Tile*);
	virtual void createPawn(Tile*);
	virtual Unit* selectUnit(Tile*, unsigned int);
	virtual void attack(Unit*, Tile*);
	virtual void moveTo(Unit*, Tile*);
	virtual void endTurn(void);
	virtual void lose(void);

private:
	Game* game;
	std::unordered_set<Unit*> units;
	std::unordered_set<Tile*> tiles;
	Hero* hero;
};

} // namespace gs

#endif
