#include <iostream>

#include "player.h"

using namespace std;

namespace gs {

Player::Player(Game* game)
{
	this->game = game;
	this->maxResources = START_MAX_RESOURCES;
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

Unit* Player::getSelectedUnit(void)
{
	return this->selectedUnit;
}

Tile* Player::getSelectedTile(void)
{
	return this->selectedTile;
}

int Player::getResources(void)
{
	return this->resources;
}

int Player::getMaxResources(void)
{
	return this->maxResources;
}

bool Player::canCreateUnit(Tile* tile)
{
	if (this->game->getTurn() != this)
		return false;
	if (tile->getPlayer() != 0 && tile->getPlayer() != this)
		return false;
	if (tile->getSize() >= tile->getUnits().size())
		return false;
	return true;
}

bool Player::canSelectUnit(Unit* unit)
{
	if (this->game->getTurn() != this)
		return false;
	if (!unit)
		return true;
	if (unit->getPlayer() != this)
		return false;
	if (unit->isMoved() && unit->isAttacked())
		return false;
	return true;
}

bool Player::canSelectTile(Tile* tile)
{
	if (this->game->getTurn() != this)
		return false;
	if (!tile)
		return true;
	if (tile->getPlayer() != this)
		return false;
	return true;
}

bool Player::canAttack(Tile* tile)
{
	if (!this->selectedUnit)
		return false;
	return this->selectedUnit->canAttack(tile);
}

bool Player::canMoveTo(Tile* tile)
{
	if (!this->selectedUnit)
		return false;
	return this->selectedUnit->canMoveTo(tile);
}

bool Player::createHero(Tile* tile)
{
	this->hero = new Hero(this, tile);
	this->addUnit(this->hero);
	tile->addUnit(this->hero);
	cout << "Player " << this << " created a hero " << this->hero << " on tile ";
	cout << tile << tile->getPosition() << endl;
	return true;
}

bool Player::createPawn(Tile* tile)
{
	if (!canCreateUnit(tile))
		return false;
	Unit* unit = new Pawn(this, tile);
	this->addUnit(unit);
	tile->addUnit(unit);
	decreaseResources(unit->getResources());
	cout << "Player " << this << " created a pawn " << unit << " on tile ";
	cout << tile << tile->getPosition() << endl;
	return true;
}

bool Player::selectUnit(Unit* unit)
{
	if (!canSelectUnit(unit))
		return false;
	this->selectedUnit = unit;
	cout << "Player " << this << " selected a unit " << unit << endl;
	return true;
}

bool Player::selectTile(Tile* tile)
{
	if (!canSelectTile(tile))
		return false;
	this->selectedTile = tile;
	cout << "Player " << this << " selected a tile " << tile << endl;
	return true;
}

bool Player::attack(Tile* tile)
{
	if (this->game->getTurn() != this)
		return false;
	if (!this->selectedUnit)
		return false;
	if (!this->selectedUnit->canAttack(tile))
		return false;
	cout << "Player " << this << " attacking tile " << tile;
	cout << " with unit " << this->selectedUnit << endl;
	this->selectedUnit->attack(tile);
	if (this->selectedUnit->getLife() <= 0) {
		this->removeUnit(this->selectedUnit);
		this->selectedUnit->getTile()->removeUnit(this->selectedUnit);
		cout << "Player " << this << " 's unit ";
		cout << this->selectedUnit << " just died" << endl;
		cerr << this->selectedUnit << ' ' << hero << endl;
		if (this->selectedUnit == this->hero)
			lose();
		delete this->selectedUnit;
	}
	return true;
}

bool Player::moveTo(Tile* tile)
{
	if (this->game->getTurn() != this)
		return false;
	if (!this->selectedUnit)
		return false;
	if (!this->selectedUnit->canMoveTo(tile))
		return false;
	cout << "Player " << this << " moving to tile " << tile;
	cout << " with unit " << this->selectedUnit << endl;
	this->selectedUnit->moveTo(tile);
	return true;
}

void Player::increaseResources(int resources)
{
	this->resources += resources;
	if (this->resources > MAX_RESOURCES)
		this->resources = MAX_RESOURCES;
}

void Player::decreaseResources(int resources)
{
	this->resources -= resources;
	if (this->resources < 0)
		this->resources = 0;
}

void Player::increaseMaxResources(int resources)
{
	this->maxResources += resources;
	if (this->maxResources > MAX_RESOURCES)
		this->maxResources = MAX_RESOURCES;
}

void Player::decreaseMaxResources(int resources)
{
	this->maxResources -= resources;
	if (this->maxResources < 0)
		this->maxResources = 0;
}

void Player::fillResources(void)
{
	this->resources = this->maxResources;
}

void Player::startTurn(void)
{
	increaseMaxResources(EACH_TURN_RESOURCES);
	fillResources();
}

void Player::endTurn(void)
{
	unordered_set<Unit*>::iterator it;
	for (it = this->units.begin(); it != this->units.end(); it++)
		(*it)->refresh();
	game->nextPlayer(this);
}

void Player::lose(void)
{
	cout << "Player " << this << " has lost the game!" << endl;
	this->game->end();
}

} // namespace gs
