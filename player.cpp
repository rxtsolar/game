#include <iostream>

#include "player.h"
#include "card-pawn.h"

using namespace std;

namespace gs {

Player::Player(Game* game)
{
	this->game = game;
	this->maxResources = START_MAX_RESOURCES;
	this->status = S_DEFAULT;
}

Player::~Player(void)
{
	unordered_set<Unit*>::iterator it;
	for (it = this->units.begin(); it != this->units.end(); it++)
		delete *it;
	for (unsigned int i = 0; i < this->cards.size(); i++)
		delete this->cards[i];
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

void Player::addCard(Card* card)
{
	if (this->cards.size() < MAX_HAND_CARDS)
		this->cards.push_back(card);
}

void Player::removeCard(Card* card)
{
	vector<Card*> newCards;
	for (unsigned int i = 0; i < this->cards.size(); i++)
		if (this->cards[i] != card)
			newCards.push_back(this->cards[i]);
	this->cards = newCards;
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

vector<Card*> Player::getCards(void)
{
	return this->cards;
}

Card* Player::getCard(unsigned int index)
{
	if (index < this->cards.size())
		return this->cards[index];
	else
		return 0;
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

Card* Player::getSelectedCard(void)
{
	return this->selectedCard;
}

int Player::getResources(void)
{
	return this->resources;
}

int Player::getMaxResources(void)
{
	return this->maxResources;
}

Status Player::getStatus(void)
{
	return this->status;
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

bool Player::canSelectCard(Card* card)
{
	if (this->game->getTurn() != this)
		return false;
	if (!card)
		return true;
	if (card->getPlayer() != this)
		return false;
	return true;
}

bool Player::canPlayCard(Tile* tile)
{
	if (!this->selectedCard)
		return false;
	return this->selectedCard->canPlay(tile);
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

bool Player::selectCard(Card* card)
{
	if (!canSelectCard(card))
		return false;
	this->selectedCard = card;
	cout << "Player " << this << " selected a card " << card << endl;
	return true;
}

bool Player::playCard(Tile* tile)
{
	if (this->game->getTurn() != this)
		return false;
	if (!this->selectedCard)
		return false;
	if (!this->selectedCard->play(tile))
		return false;
	removeCard(this->selectedCard);
	delete this->selectedCard;
	this->selectedCard = 0;
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

bool Player::drawCard(void)
{
	if (this->cards.size() >= MAX_HAND_CARDS)
		return false;
	addCard(new CardPawn(this));
	return true;
}

void Player::increaseResources(unsigned int resources)
{
	this->resources += resources;
	if (this->resources > MAX_RESOURCES)
		this->resources = MAX_RESOURCES;
}

void Player::decreaseResources(unsigned int resources)
{
	if (this->resources < resources)
		this->resources = 0;
	else
		this->resources -= resources;
}

void Player::increaseMaxResources(unsigned int resources)
{
	this->maxResources += resources;
	if (this->maxResources > MAX_RESOURCES)
		this->maxResources = MAX_RESOURCES;
}

void Player::decreaseMaxResources(unsigned int resources)
{
	if (this->maxResources < resources)
		this->maxResources = 0;
	else
		this->maxResources -= resources;
}

void Player::fillResources(void)
{
	this->resources = this->maxResources;
}

void Player::setStatus(Status status)
{
	this->status = status;
}

void Player::startTurn(void)
{
	increaseMaxResources(EACH_TURN_RESOURCES);
	drawCard();
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
