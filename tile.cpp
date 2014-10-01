#include <iostream>
#include <cmath>

#include "tile.h"

using namespace std;

namespace gs {

Tile::Tile(unsigned int x, unsigned int y, unsigned int limit)
{
	this->size = 0;
	this->position.x = x;
	this->position.y = y;
	this->units = vector<Unit*>(limit);
	this->player = 0;
}

Tile::~Tile(void)
{

}

unsigned int Tile::getSize(void)
{
	return this->size;
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

vector<Unit*> Tile::getUnits(void)
{
	return this->units;
}

Unit* Tile::getUnit(unsigned int i)
{
	if (i >= this->size) {
		cerr << "getUnit failed: index " << i;
		cerr << " out of boundary" << endl;
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
	if (this->size >= this->units.size()) {
		cerr << "addUnit failed: tile " << this << " is full.";
		cerr << " size: " << this->size;
		cerr << " limit: " << this->units.size() << endl;
		return;
	}
	this->player = unit->getPlayer();
	this->units[this->size] = unit;
	this->size++;
}

void Tile::removeUnit(Unit* unit)
{
	unsigned int i = 0;
	for (unsigned int j = 0; j < this->units.size(); j++) {
		if (this->units[j] != unit) {
			this->units[i] = this->units[j];
			i++;
		} else {
			this->size--;
		}
	}
	while (i < this->units.size()) {
		this->units[i] = 0;
		i++;
	}

	if (this->size == 0) {
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
	unsigned int oldSize = this->size;
	unsigned int i = 0;
	while (i < this->size) {
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
			this->units[i] = 0;
		}
		i++;
	}

	i = 0;
	for (unsigned int j = 0; j < oldSize; j++) {
		if (this->units[j] != 0) {
			this->units[i] = this->units[j];
			i++;
		} else {
			this->size--;
		}
	}
	while (i < this->units.size()) {
		this->units[i] = 0;
		i++;
	}

	if (this->size == 0) {
		this->player->removeTile(this);
		this->player = 0;
	}
}

} // namespace gs
