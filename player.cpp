#include "player.h"

using namespace std;

namespace gs {

Player::Player(void)
{

}

Player::~Player(void)
{
	unordered_set<Unit*>::iterator it;
	for (it = this->units.begin(); it != this->units.end(); it++)
		delete *it;
}

void Player::addUnit(Unit* unit)
{
	this->units.insert(unit);
}

void Player::removeUnit(Unit* unit)
{
	this->units.erase(unit);
}

void Player::addTile(Tile* tile)
{
	this->tiles.insert(tile);
}

void Player::removeTile(Tile* tile)
{
	this->tiles.erase(tile);
}

unordered_set<Unit*> Player::getUnits(void)
{
	return this->units;
}

unordered_set<Tile*> Player::getTiles(void)
{
	return this->tiles;
}

bool Player::canCreateUnit(Tile* tile)
{
	if (tile->getPlayer() == 0 || tile->getPlayer() == this)
		return true;
	return false;
}

void Player::createUnit(Tile* tile)
{
	if (!canCreateUnit(tile))
		return;
	Unit* unit = new Unit(this, tile);
	this->addUnit(unit);
	tile->addUnit(unit);
}

} // namespace gs
