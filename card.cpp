#include <string>
#include <SDL/SDL_ttf.h>

#include "card.h"

using namespace std;

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

void UnitCard::render(SDL_Surface* screen, SDL_Rect* box)
{
	TTF_Font* font = TTF_OpenFont(font_path, box->h / 6 * font_rate);
	Uint32 color;

	switch (getPlayer()->getStatus()) {
	case S_CARD:
		if (getPlayer()->getSelectedCard() == this)
			color = SDL_MapRGB(screen->format, 0x6f, 0xff, 0xff);
		else
			color = SDL_MapRGB(screen->format, 0xaf, 0xaf, 0xaf);
		break;
	default:
		color = SDL_MapRGB(screen->format, 0xaf, 0xaf, 0xaf);
		break;
	}

	string resource = to_string(getResources());
	string description = getDescription();
	string damage = to_string(getDamage());
	string life = to_string(getLife());
	SDL_Color fontColor = { 0x0f, 0x0f, 0x0f };
	SDL_Surface* r = TTF_RenderText_Blended(font,
			resource.c_str(), fontColor);
	SDL_Surface* desc = TTF_RenderText_Blended(font,
			description.c_str(), fontColor);
	SDL_Surface* d = TTF_RenderText_Blended(font,
			damage.c_str(), fontColor);
	SDL_Surface* l = TTF_RenderText_Blended(font,
			life.c_str(), fontColor);
	SDL_Rect offset;

	SDL_FillRect(screen, box, color);
	offset.x = box->x;
	offset.y = box->y;
	SDL_BlitSurface(r, 0, screen, &offset);
	offset.x = box->x + (Sint16)(box->w - desc->w) / 2;
	offset.y = box->y + (Sint16)(box->h - desc->h) / 2;
	SDL_BlitSurface(desc, 0, screen, &offset);
	offset.y = box->y + (Sint16)(box->h * 5 / 6);
	offset.x = box->x;
	SDL_BlitSurface(d, 0, screen, &offset);
	offset.x = box->x + (Sint16)(box->w * 3 / 4);
	SDL_BlitSurface(l, 0, screen, &offset);

	SDL_FreeSurface(r);
	SDL_FreeSurface(desc);
	SDL_FreeSurface(d);
	SDL_FreeSurface(l);

	TTF_CloseFont(font);
}

} // namespace gs
