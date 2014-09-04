#include <iostream>
#include <cmath>

#include "tile.h"

using namespace std;

namespace gs {

Tile::Tile(int x, int y)
{
	this->position.x = x;
	this->position.y = y;
}

Tile::~Tile(void)
{

}

Position Tile::getPosition(void)
{
	return this->position;
}

int Tile::getDistance(Tile* tile)
{
	int distance = 0;

	distance += abs(tile->position.x - this->position.x);
	distance += abs(tile->position.y - this->position.y);
	return distance;
}

list<Unit*> Tile::getUnits(void)
{
	return this->units;
}

Player* Tile::getPlayer(void)
{
	return this->player;
}

void Tile::setPosition(const Position& position)
{
	this->position = position;
}

void Tile::addUnit(Unit* unit)
{
	this->units.push_back(unit);
	this->player = unit->getPlayer();
}

void Tile::removeUnit(Unit* unit)
{
	this->units.remove(unit);
	if (this->units.empty()) {
		this->player->removeTile(this);
		this->player = 0;
	}
}

void Tile::setPlayer(Player* player)
{
	this->player = player;
}

void Tile::attackedBy(Unit* unit)
{
	list<Unit*>::iterator it = this->units.begin();

	while (it != this->units.end()) {
		Unit* u = *it;
		unit->attack(u);
		if (u->canAttack(unit->getTile()))
			u->attack(unit);
		if (u->getLife() > 0) {
			it++;
		} else {
			this->player->removeUnit(u);
			this->units.erase(it);
			cout << "Player " << u->getPlayer() << " 's unit ";
			cout << u << " just died" << endl;
			delete u;
		}
	}

	if (this->units.empty()) {
		this->player->removeTile(this);
		this->player = 0;
	}

	if (unit->getLife() <= 0) {
		unit->getPlayer()->removeUnit(unit);
		unit->getTile()->removeUnit(unit);
		cout << "Player " << unit->getPlayer() << " 's unit ";
		cout << unit << " just died" << endl;
		delete unit;
	}
}

} // namespace gs
