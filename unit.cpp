#include <iostream>

#include "unit.h"

using namespace std;

namespace gs {

Unit::Unit(Player* player, Tile* tile)
{
	this->moved = true;
	this->attacked = true;

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

int Unit::getMoveRange(void)
{
	return this->moveRange;
}

int Unit::getAttackRange(void)
{
	return this->attackRange;
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

void Unit::setMoveRange(int moveRange)
{
	this->moveRange = moveRange;
}

void Unit::setAttackRange(int attackRange)
{
	this->attackRange = attackRange;
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
	if (this->moved) {
		cerr << "Player " << this->player << " 's unit " << this;
		cerr << " has already moved" << endl;
		return false;
	}

	if (this->tile->getDistance(tile) > 1) {
		cerr << "Player " << this->player << " 's unit " << this;
		cerr << " could not move from " << this->tile->getPosition();
		cerr << " to " << tile->getPosition() << endl;
		return false;
	}

	if (tile->getPlayer() == 0) {
		return true;
	} else if (tile->getPlayer() == this->tile->getPlayer()) {
		return true;
	} else {
		cerr << "Player " << this->player << " 's unit " << this;
		cerr << " could not move to" << tile->getPosition();
		cerr << " because player " << tile->getPlayer();
		cerr << " is there" << endl;
		return false;
	}
}

bool Unit::canAttack(Tile* tile)
{
	if (this->attacked) {
		cerr << "Player " << this->player << " 's unit " << this;
		cerr << " has already attacked" << endl;
		return false;
	}

	if (this->tile->getDistance(tile) > 1) {
		cerr << "Player " << this->player << " 's unit " << this;
		cerr << " could not attack " << tile->getPosition();
		cerr << " from " << this->tile->getPosition() << endl;
		return false;
	}

	if (tile->getPlayer() == 0) {
		cerr << "Player " << this->player << " 's unit " << this;
		cerr << " could not attack " << tile->getPosition();
		cerr << " because no one is there" << endl;
		return false;
	} else if (tile->getPlayer() == this->tile->getPlayer()) {
		cerr << "Player " << this->player << " 's unit " << this;
		cerr << " could not attack " << tile->getPosition();
		cerr << " because friend units are there" << endl;
		return false;
	} else {
		return true;
	}
}

void Unit::refresh(void)
{
	this->moved = false;
	this->attacked = false;
	cout << "Player " << this->player << " 's unit " << this;
	cout << " refreshed" << endl;
}

void Unit::moveTo(Tile* tile)
{
	if (!canMoveTo(tile))
		return;

	this->tile->removeUnit(this);
	tile->addUnit(this);
	cout << "Player " << this->player << " 's unit " << this;
	cout << " moved from " << this->tile << " to " << tile;
	cout << endl;
	this->tile = tile;

	this->moved = true;
}

void Unit::attack(Tile* tile)
{
	if (!canAttack(tile))
		return;

	cout << "Player " << this->player << " 's unit " << this;
	cout << " attacking from " << this->tile << " to " << tile;
	cout << endl;

	tile->attackedBy(this);

	this->attacked = true;
}

void Unit::attack(Unit* unit)
{
	cout << "Player " << this->player << " 's unit " << this;
	cout << " attacking unit " << unit << endl;
	unit->setLife(unit->getLife() - this->damage);
}


Hero::Hero(Player* player, Tile* tile) : Unit(player, tile)
{
	setLife(5);
	setDamage(2);
	setMoveRange(2);
	setAttackRange(2);
}

Hero::~Hero(void)
{

}


Pawn::Pawn(Player* player, Tile* tile) : Unit(player, tile)
{
	setLife(2);
	setDamage(1);
	setMoveRange(1);
	setAttackRange(1);
}

Pawn::~Pawn(void)
{

}

} // namespace gs
