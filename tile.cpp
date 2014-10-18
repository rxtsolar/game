#include <iostream>

#include "tile.h"

using namespace std;

namespace gs {

static inline int diff(unsigned int a, unsigned int b)
{
	return a > b ? a - b : b - a;
}

Tile::Tile(unsigned int x, unsigned int y)
{
	this->position.x = x;
	this->position.y = y;
	this->player = 0;
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

	distance += diff(tile->position.x, this->position.x);
	distance += diff(tile->position.y, this->position.y);
	return distance;
}

vector<Unit*> Tile::getUnits(void)
{
	return this->units;
}

Unit* Tile::getUnit(unsigned int i)
{
	if (i >= this->units.size()) {
		return 0;
	}
	return this->units[i];
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
	if (this->units.size() < MAX_TILE_UNITS) {
		this->player = unit->getPlayer();
		this->units.push_back(unit);
	}
}

void Tile::removeUnit(Unit* unit)
{
	vector<Unit*> newUnits;
	for (unsigned int i = 0; i < this->units.size(); i++)
		if (this->units[i] != unit)
			newUnits.push_back(this->units[i]);
	this->units = newUnits;

	if (this->units.size() == 0) {
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
	vector<Unit*> newUnits;

	for (unsigned int i = 0; i < this->units.size(); i++) {
		Unit* u = this->units[i];
		unit->attack(u);
		if (u->canAttack(unit->getTile()))
			u->attack(unit);
		if (u->getLife() <= 0) {
			this->player->removeUnit(u);
			cout << "Player " << u->getPlayer() << " 's unit ";
			cout << u << " just died" << endl;
			if (u == u->getPlayer()->getHero())
				u->getPlayer()->lose();
			delete u;
		} else {
			newUnits.push_back(u);
		}
	}
	this->units = newUnits;

	if (this->units.size() == 0) {
		this->player->removeTile(this);
		this->player = 0;
	}
}

} // namespace gs
