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

unsigned int Card::getDefaultResources(void)
{
	return this->defaultResources;
}

unsigned int Card::getResources(void)
{
	return this->resources;
}

void Card::setPlayer(Player* player)
{
	this->player = player;
}

void Card::setDefaultResources(unsigned int defaultResources)
{
	this->defaultResources = defaultResources;
}

void Card::setResources(unsigned int resources)
{
	this->resources = resources;
}

void Card::render(SDL_Surface* screen, SDL_Rect* box)
{
	if (getPlayer()->canSelectCard(this)) {
		SDL_Rect frame;
		Uint32 frameColor = SDL_MapRGB(screen->format, 0x6f, 0xff, 0xff);
		frame.x = box->x - 3;
		frame.y = box->y - 3;
		frame.w = box->w + 6;
		frame.h = box->h + 6;
		SDL_FillRect(screen, &frame, frameColor);
	}
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
	string resource = to_string(getResources());
	string moveRange = to_string(getMoveRange());
	string description = getDescription();
	string damage = to_string(getDamage());
	string life = to_string(getLife());
	SDL_Color fontColor = { 0x0f, 0x0f, 0x0f };
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
	SDL_Rect offset;
	Uint32 color;

	Card::render(screen, box);

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
}

} // namespace gs
