#include <iostream>

#include <SDL/SDL_ttf.h>

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

int Unit::getResources(void)
{
	return this->resources;
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

void Unit::setResources(int resources)
{
	this->resources = resources;
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
	if (this->tile->getDistance(tile) > this->moveRange)
		return false;
	if (tile->getUnits().size() >= MAX_TILE_UNITS)
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
	if (this->tile->getDistance(tile) > this->attackRange)
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

void Unit::render(SDL_Surface* screen, SDL_Rect* box)
{
	switch (getPlayer()->getStatus()) {
	case S_TILE:
	{
		TTF_Font* font = TTF_OpenFont(font_path, box->h / 6 * font_rate);
		string resource = to_string(getResources());
	    string moveRange = to_string(getMoveRange());
		string description = getDescription();
		string damage = to_string(getDamage());
		string life = to_string(getLife());
		SDL_Color fontColor = { 0xff, 0xff, 0xff };

		SDL_Surface* r = TTF_RenderText_Blended(font,
				resource.c_str(), fontColor);
		SDL_Surface* m = TTF_RenderText_Blended(font,
				moveRange.c_str(), fontColor);
		SDL_Surface* desc = TTF_RenderText_Blended(font,
				description.c_str(), fontColor);
		SDL_Surface* d = TTF_RenderText_Blended(font,
				damage.c_str(), fontColor);
		SDL_Surface* l = TTF_RenderText_Blended(font,
				life.c_str(), fontColor);
		Uint32 color = SDL_MapRGB(screen->format, 0x3f, 0x3f, 0x3f);
		SDL_Rect offset;

		if (getPlayer()->canSelectUnit(this)) {
			SDL_Rect frame;
			Uint32 frameColor = SDL_MapRGB(screen->format, 0x6f, 0xff, 0xff);
			frame.x = box->x - 3;
			frame.y = box->y - 3;
			frame.w = box->w + 6;
			frame.h = box->h + 6;
			SDL_FillRect(screen, &frame, frameColor);
		}   

		SDL_FillRect(screen, box, color);
		offset.x = box->x;
		offset.y = box->y;
		SDL_BlitSurface(r, 0, screen, &offset);
		offset.x = box->x + (Sint16)(box->w * 3 / 4);
		SDL_BlitSurface(m, 0, screen, &offset);
		offset.x = box->x + (Sint16)(box->w - desc->w) / 2;
		offset.y = box->y + (Sint16)(box->h - desc->h) / 2;
		SDL_BlitSurface(desc, 0, screen, &offset);
		offset.y = box->y + (Sint16)(box->h * 5 / 6);
		offset.x = box->x;
		SDL_BlitSurface(d, 0, screen, &offset);
		offset.x = box->x + (Sint16)(box->w * 3 / 4);
		SDL_BlitSurface(l, 0, screen, &offset);

		SDL_FreeSurface(r);
		SDL_FreeSurface(m);
		SDL_FreeSurface(desc);
		SDL_FreeSurface(d);
		SDL_FreeSurface(l);

		TTF_CloseFont(font);
		break;
	}
	default:
		break;
	}
}


Hero::Hero(Player* player, Tile* tile) : Unit(player, tile)
{
	setLife(5);
	setDamage(2);
	setMoveRange(2);
	setAttackRange(2);
	setResources(10);
}

Hero::~Hero(void)
{

}

string Hero::getDescription(void)
{
	return "Hero";
}

} // namespace gs
