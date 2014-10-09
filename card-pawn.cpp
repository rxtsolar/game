#include <iostream>

#include "card-pawn.h"

using namespace std;

namespace gs {

CardPawn::CardPawn(void)
{
	setDefaultResources(1);
	setResources(1);
	setLife(2);
	setDamage(1);
	setMoveRange(1);
	setAttackRange(1);
}

CardPawn::~CardPawn(void)
{

}

bool CardPawn::canPlay(Player* player, Tile* tile)
{
	if (player->getGame()->getTurn() != player)
		return false;
	if (tile->getPlayer() != 0 && tile->getPlayer() != player)
		return false;
	if (tile->getSize() >= tile->getUnits().size())
		return false;
	return true;
}

bool CardPawn::play(Player* player, Tile* tile)
{
	if (!canPlay(player, tile))
		return false;
	Unit* unit = new UnitPawn(player, tile);
	player->addUnit(unit);
	tile->addUnit(unit);
	player->decreaseResources(getResources());
	cout << "Player " << player << " created a pawn " << unit << " on tile ";
	cout << tile << tile->getPosition() << endl;
	return true;
}


UnitPawn::UnitPawn(Player* player, Tile* tile) : Unit(player, tile)
{
	setResources(1);
	setLife(2);
	setDamage(1);
	setMoveRange(1);
	setAttackRange(1);
}

UnitPawn::~UnitPawn(void)
{

}

} // namespace gs
