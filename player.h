#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <unordered_set>

#include "unit.h"

namespace gs {

class Unit;
class Tile;

class Player {
public:
	Player(void);
	virtual ~Player(void);

	virtual void addUnit(Unit*);
	virtual void removeUnit(Unit*);
	virtual void addTile(Tile*);
	virtual void removeTile(Tile*);

	virtual std::unordered_set<Unit*> getUnits(void);
	virtual std::unordered_set<Tile*> getTiles(void);

	virtual bool canCreateUnit(Tile*);
	virtual bool canSelectUnit(Tile*, unsigned int i);

	virtual void createHero(Tile*);
	virtual void createPawn(Tile*);
	virtual Unit* selectUnit(Tile*, unsigned int);
	virtual void attack(Unit*, Tile*);
	virtual void refreshUnits(void);

private:
	std::unordered_set<Unit*> units;
	std::unordered_set<Tile*> tiles;
};

} // namespace gs

#endif
