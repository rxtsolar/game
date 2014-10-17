#ifndef _CARD_PAWN_H_
#define _CARD_PAWN_H_

#include "card.h"
#include "unit.h"

namespace gs {

class CardPawn : public UnitCard {
public:
	CardPawn(Player* player);
	virtual ~CardPawn(void);

	virtual bool canPlay(Tile*);
	virtual bool play(Tile*);
	virtual std::string getDescription(void);
};

class UnitPawn : public Unit {
public:
	UnitPawn(Player*, Tile*);
	virtual ~UnitPawn(void);
	virtual std::string getDescription(void);
};

} // namespace gs

#endif
