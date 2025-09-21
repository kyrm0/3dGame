#include "Rectangle.h"

Rectangle::Rectangle(float x, float y, int w, int h, SDL_Color color, int id)
	: object(x, y, w, h, color, id) {}

void Rectangle::draw(SDL_Renderer* renderer)
{
	object::draw(renderer);

	SDL_FRect rect = { (float)x, (float)y, (float)width, (float)height };
	SDL_RenderFillRect(renderer, &rect);
}
