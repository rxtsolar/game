#ifndef _UNIT_H_
#define _UNIT_H_

#include "player.h"
#include "tile.h"

namespace gs {

class Player;
class Tile;

class Unit {
public:
	Unit(Player*, Tile*);
	virtual ~Unit(void);

	virtual int getLife(void);
	virtual int getDamage(void);
	virtual Player* getPlayer(void);
	virtual Tile* getTile(void);

	virtual void setLife(int);
	virtual void setDamage(int);
	virtual void setPlayer(Player*);
	virtual void setTile(Tile*);

	virtual bool isMoved(void);
	virtual bool isAttacked(void);
	virtual bool canMoveTo(Tile*);
	virtual bool canAttack(Tile*);

	virtual void refresh(void);
	virtual void moveTo(Tile*);
	virtual void attack(Tile*);
	virtual void attack(Unit*);

private:
	bool moved;
	bool attacked;

	int life;
	int damage;

	Player* player;
	Tile* tile;
};

} // namespace gs

#endif
