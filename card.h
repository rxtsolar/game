#ifndef _CARD_H_
#define _CARD_H_

#include "player.h"
#include "tile.h"

namespace gs {

class Player;
class Tile;

class Card {
public:
	Card(void);
	virtual ~Card(void);

	virtual int getDefaultResources(void);
	virtual int getResources(void);

	virtual void setDefaultResources(int);
	virtual void setResources(int);

	virtual bool canPlay(Player*, Tile*) = 0;
	virtual bool play(Player*, Tile*) = 0;
private:
	int defaultResources;
	int resources;
};

class UnitCard : public Card {
public:
	UnitCard(void);
	virtual ~UnitCard(void);

	virtual int getLife(void);
	virtual int getDamage(void);
	virtual int getMoveRange(void);
	virtual int getAttackRange(void);

	virtual void setLife(int);
	virtual void setDamage(int);
	virtual void setMoveRange(int);
	virtual void setAttackRange(int);

	virtual bool canPlay(Player*, Tile*) = 0;
	virtual bool play(Player*, Tile*) = 0;
private:
	int life;
	int damage;
	int moveRange;
	int attackRange;
};

} // namespace gs

#endif
