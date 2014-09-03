#include "unit.h"

namespace gs {

Unit::Unit(Player* player, Tile* tile)
{
	this->moved = true;
	this->attacked = true;

	this->life = 1;
	this->damage = 1;

	this->player = player;
	this->tile = tile;
}

Unit::~Unit(void)
{

}

int Unit::getLife(void)
{
	return this->life;
}

int Unit::getDamage(void)
{
	return this->damage;
}

Player* Unit::getPlayer(void)
{
	return this->player;
}

Tile* Unit::getTile(void)
{
	return this->tile;
}

void Unit::setLife(int life)
{
	this->life = life;
}

void Unit::setDamage(int damage)
{
	this->damage = damage;
}

void Unit::setPlayer(Player* player)
{
	this->player = player;
}

void Unit::setTile(Tile* tile)
{
	this->tile = tile;
}

bool Unit::isMoved(void)
{
	return this->moved;
}

bool Unit::isAttacked(void)
{
	return this->attacked;
}

bool Unit::canMoveTo(Tile* tile)
{
	if (this->moved)
		return false;

	if (this->tile->getDistance(tile) > 1)
		return false;

	if (tile->getPlayer() == 0)
		return true;
	else if (tile->getPlayer() == this->tile->getPlayer())
		return true;
	else
		return false;
}

bool Unit::canAttack(Tile* tile)
{
	if (this->attacked)
		return false;

	if (this->tile->getDistance(tile) > 1)
		return false;

	if (tile->getPlayer() == 0)
		return false;
	else if (tile->getPlayer() == this->tile->getPlayer())
		return false;
	else
		return true;
}

void Unit::refresh(void)
{
	this->moved = false;
	this->attacked = false;
}

void Unit::moveTo(Tile* tile)
{
	if (!canMoveTo(tile))
		return;

	this->tile->removeUnit(this);
	tile->addUnit(this);
	this->tile = tile;

	this->moved = true;
}

void Unit::attack(Tile* tile)
{
	if (!canAttack(tile))
		return;

	tile->attackedBy(this);

	this->attacked = true;
}

void Unit::attack(Unit* unit)
{
	unit->setLife(unit->getLife() - this->damage);
}

} // namespace gs
