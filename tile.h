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
	Tile(unsigned int x, unsigned int y, unsigned int limit);
	virtual ~Tile(void);

	virtual unsigned int getSize(void);
	virtual Position getPosition(void);
	virtual int getDistance(Tile*);
	virtual std::vector<Unit*> getUnits(void);
	virtual Unit* getUnit(unsigned int);
	virtual Player* getPlayer(void);

	virtual void setPosition(const Position&);
	virtual void addUnit(Unit*);
	virtual void removeUnit(Unit*);
	virtual void setPlayer(Player*);

	virtual void attackedBy(Unit*);

private:
	unsigned int size;
	Position position;
	std::vector<Unit*> units;
	Player* player;
};

} // namespace gs

#endif
