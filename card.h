#ifndef _CARD_H_
#define _CARD_H_

#include <SDL/SDL.h>

#include "player.h"
#include "tile.h"

namespace gs {

class Player;
class Tile;

class Card {
public:
	Card(Player* player);
	virtual ~Card(void);

	virtual Player* getPlayer(void);
	virtual int getDefaultResources(void);
	virtual int getResources(void);

	virtual void setPlayer(Player*);
	virtual void setDefaultResources(int);
	virtual void setResources(int);

	virtual bool canPlay(Tile*) = 0;
	virtual bool play(Tile*) = 0;
	virtual std::string getDescription(void) = 0;
	virtual void render(SDL_Surface*, SDL_Rect*) = 0;
private:
	Player* player;
	int defaultResources;
	int resources;
};

class UnitCard : public Card {
public:
	UnitCard(Player* player);
	virtual ~UnitCard(void);

	virtual int getLife(void);
	virtual int getDamage(void);
	virtual int getMoveRange(void);
	virtual int getAttackRange(void);

	virtual void setLife(int);
	virtual void setDamage(int);
	virtual void setMoveRange(int);
	virtual void setAttackRange(int);

	virtual void render(SDL_Surface*, SDL_Rect*);
private:
	int life;
	int damage;
	int moveRange;
	int attackRange;
};

} // namespace gs

#endif
