#ifndef _CARD_PAWN_H_
#define _CARD_PAWN_H_

#include "card.h"
#include "unit.h"

namespace gs {

class CardPawn : public UnitCard {
public:
	CardPawn(void);
	virtual ~CardPawn(void);

	virtual bool canPlay(Player*, Tile*);
	virtual bool play(Player*, Tile*);
};

class UnitPawn : public Unit {
public:
	UnitPawn(Player*, Tile*);
	virtual ~UnitPawn(void);
};

} // namespace gs

#endif
