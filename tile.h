#ifndef _TILE_H_
#define _TILE_H_

#include <list>

#include "basic.h"
#include "player.h"
#include "unit.h"

namespace gs {

class Player;
class Unit;

class Tile {
public:
	Tile(int x, int y);
	virtual ~Tile(void);

	virtual Position getPosition(void);
	virtual int getDistance(Tile*);
	virtual std::list<Unit*> getUnits(void);
	virtual Player* getPlayer(void);

	virtual void setPosition(const Position&);
	virtual void addUnit(Unit*);
	virtual void removeUnit(Unit*);
	virtual void setPlayer(Player*);

	virtual void attackedBy(Unit*);

private:
	Position position;
	std::list<Unit*> units;
	Player* player;
};

} // namespace gs

#endif
