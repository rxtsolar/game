#include "card.h"

namespace gs {

Card::Card(Player* player)
{
	this->player = player;
}

Card::~Card(void)
{

}

Player* Card::getPlayer(void)
{
	return this->player;
}

int Card::getDefaultResources(void)
{
	return this->defaultResources;
}

int Card::getResources(void)
{
	return this->resources;
}

void Card::setPlayer(Player* player)
{
	this->player = player;
}

void Card::setDefaultResources(int defaultResources)
{
	this->defaultResources = defaultResources;
}

void Card::setResources(int resources)
{
	this->resources = resources;
}


UnitCard::UnitCard(Player* player) : Card(player)
{

}

UnitCard::~UnitCard(void)
{

}

int UnitCard::getLife(void)
{
	return this->life;
}

int UnitCard::getDamage(void)
{
	return this->damage;
}

int UnitCard::getMoveRange(void)
{
	return this->moveRange;
}

int UnitCard::getAttackRange(void)
{
	return this->attackRange;
}

void UnitCard::setLife(int life)
{
	this->life = life;
}

void UnitCard::setDamage(int damage)
{
	this->damage = damage;
}

void UnitCard::setMoveRange(int moveRange)
{
	this->moveRange = moveRange;
}

void UnitCard::setAttackRange(int attackRange)
{
	this->attackRange = attackRange;
}

} // namespace gs
