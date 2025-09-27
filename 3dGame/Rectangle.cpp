#include "Rectangle.h"


void Rect::draw(SDL_Renderer* renderer, bool onlyOutline)
{
	object::draw(renderer, onlyOutline);

	SDL_FRect rect = { (float)x, (float)y, (float)width, (float)height };
	if (!onlyOutline) SDL_RenderFillRect(renderer, &rect);
	else
	{
		SDL_RenderRect(renderer, &rect);
	}
}
