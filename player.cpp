#include <iostream>

#include "player.h"

using namespace std;

namespace gs {

Player::Player(Game* game)
{
	this->game = game;
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

Game* Player::getGame(void)
{
	return this->game;
}

unordered_set<Unit*> Player::getUnits(void)
{
	return this->units;
}

unordered_set<Tile*> Player::getTiles(void)
{
	return this->tiles;
}

Hero* Player::getHero(void)
{
	return this->hero;
}

bool Player::canCreateUnit(Tile* tile)
{
	if (this->game->getTurn() != this)
		return false;
	if (tile->getPlayer() == 0 || tile->getPlayer() == this)
		return true;
	return false;
}

bool Player::canSelectUnit(Tile* tile, unsigned int i)
{
	if (this->game->getTurn() != this)
		return false;
	if (tile->getPlayer() != this)
		return false;
	if (i >= tile->getSize())
		return false;
	return true;
}

void Player::createHero(Tile* tile)
{
	Unit* unit = new Hero(this, tile);
	this->addUnit(unit);
	tile->addUnit(unit);
	cout << "Player " << this << " created a hero " << unit << " on tile ";
	cout << tile << tile->getPosition() << endl;
}

void Player::createPawn(Tile* tile)
{
	if (!canCreateUnit(tile))
		return;
	Unit* unit = new Pawn(this, tile);
	this->addUnit(unit);
	tile->addUnit(unit);
	cout << "Player " << this << " created a pawn " << unit << " on tile ";
	cout << tile << tile->getPosition() << endl;
}

Unit* Player::selectUnit(Tile* tile, unsigned int i)
{
	Unit* unit;
	if (!canSelectUnit(tile, i))
		return 0;
	unit = tile->getUnits()[i];
	cout << "Player " << this << " selected a unit " << unit << endl;;
	return unit;
}

void Player::attack(Unit* unit, Tile* tile)
{
	if (this->game->getTurn() != this)
		return;
	if (unit->getPlayer() != this)
		return;
	cout << "Player " << this << " attacking tile " << tile;
	cout << " with unit " << unit << endl;
	unit->attack(tile);

        if (unit->getLife() <= 0) {
                this->removeUnit(unit);
                unit->getTile()->removeUnit(unit);
                cout << "Player " << this << " 's unit ";
                cout << unit << " just died" << endl;
                delete unit;
        }
}

void Player::endTurn(void)
{
	unordered_set<Unit*>::iterator it;
	for (it = this->units.begin(); it != this->units.end(); it++)
		(*it)->refresh();
	game->nextPlayer(this);
}

} // namespace gs
