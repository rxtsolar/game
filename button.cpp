#include "button.h"

using namespace std;

namespace gs {

Button::Button(Activity* activity)
{
	this->activity = activity;
	this->box = new SDL_Rect();
	this->status = S_DEFAULT;
}

Button::Button(Activity* activity, int x, int y, int w, int h)
{
	this->activity = activity;
	this->box = new SDL_Rect();
	this->box->x = x;
	this->box->y = y;
	this->box->w = w;
	this->box->h = h;
	this->status = S_DEFAULT;
}

Button::~Button(void)
{
	delete this->box;
}

SDL_Rect* Button::getBox(void)
{
	return this->box;
}

Activity* Button::getActivity(void)
{
	return this->activity;
}

Status Button::getStatus(void)
{
	return this->status;
}

void Button::setBox(int x, int y, int w, int h)
{
	this->box->x = x;
	this->box->y = y;
	this->box->w = w;
	this->box->h = h;
}

void Button::setStatus(Status status)
{
	this->status = status;
}

void Button::handle(SDL_Event* event)
{
	int x;
	int y;

	if (event->type == SDL_MOUSEMOTION) {
		x = event->motion.x;
		y = event->motion.y;

		if (x > this->box->x && x < this->box->x + this->box->w &&
				y > this->box->y && y < this->box->y + this->box->h)
			inside();
		else
			outside();
	}
	if (event->type == SDL_MOUSEBUTTONDOWN) {
		x = event->button.x;
		y = event->button.y;

		if (x > this->box->x && x < this->box->x + this->box->w &&
				y > this->box->y && y < this->box->y + this->box->h) {
			if (event->button.button == SDL_BUTTON_LEFT)
				leftClick();
			else if (event->button.button == SDL_BUTTON_RIGHT)
				rightClick();
		}
	}
}

void Button::render(SDL_Surface* screen)
{
	SDL_FillRect(screen, this->box,
			SDL_MapRGB(screen->format, 0xaf, 0xaf, 0xaf));
}

void Button::inside(void)
{

}

void Button::outside(void)
{

}

void Button::leftClick(void)
{

}

void Button::rightClick(void)
{

}


TextButton::TextButton(Activity* activity, const char* text,
					   int x, int y, int w, int h) :
	Button(activity, x, y, w, h)
{
	this->text = text;
	this->font = TTF_OpenFont(font_path, h * font_rate);
}

TextButton::~TextButton(void)
{
	if (this->font)
		TTF_CloseFont(this->font);
}

void TextButton::render(SDL_Surface* screen)
{
	SDL_Color color = { 0x0f, 0x0f, 0x0f };
	SDL_Rect offset;
	SDL_Rect* box = getBox();
	SDL_Surface* message = TTF_RenderText_Blended(this->font, text, color);

	SDL_FillRect(screen, this->getBox(),
			SDL_MapRGB(screen->format, 0xaf, 0xaf, 0xaf));
	offset.x = box->x + (box->w - message->w) / 2;
	offset.y = box->y + (box->h - message->h) / 2;
	SDL_BlitSurface(message, 0, screen, &offset);

	SDL_FreeSurface(message);
}

} // namespace gs
