#ifndef _TILE_H_
#define _TILE_H_

#include <vector>

#include "basic.h"
#include "player.h"
#include "unit.h"

namespace gs {

class Player;
class Unit;

class Tile {
public:
	Tile(int x, int y, int limit);
	virtual ~Tile(void);

	virtual int getSize(void);
	virtual Position getPosition(void);
	virtual int getDistance(Tile*);
	virtual std::vector<Unit*> getUnits(void);
	virtual Unit* getUnit(int);
	virtual Player* getPlayer(void);

	virtual void setPosition(const Position&);
	virtual void addUnit(Unit*);
	virtual void removeUnit(Unit*);
	virtual void setPlayer(Player*);

	virtual void attackedBy(Unit*);

private:
	int size;
	Position position;
	std::vector<Unit*> units;
	Player* player;
};

} // namespace gs

#endif
