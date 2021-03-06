#include <iostream>

#include <SDL/SDL_ttf.h>

#include "card-pawn.h"

using namespace std;

namespace gs {

CardPawn::CardPawn(Player* player) : UnitCard(player)
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

bool CardPawn::canPlay(Tile* tile)
{
	if (getPlayer()->getGame()->getTurn() != getPlayer())
		return false;
	if (tile->getPlayer() != 0 && tile->getPlayer() != getPlayer())
		return false;
	if (tile->getUnits().size() >= MAX_TILE_UNITS)
		return false;
	return true;
}

bool CardPawn::play(Tile* tile)
{
	if (!canPlay(tile))
		return false;
	Unit* unit = new UnitPawn(getPlayer(), tile);
	getPlayer()->addUnit(unit);
	tile->addUnit(unit);
	getPlayer()->decreaseResources(getResources());
	cout << "Player " << getPlayer() << " created a pawn " << unit << " on tile ";
	cout << tile << tile->getPosition() << endl;
	return true;
}

string CardPawn::getDescription(void)
{
	string description = "Pawn";
	return description;
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

string UnitPawn::getDescription(void)
{
	return "Pawn";
}

} // namespace gs
