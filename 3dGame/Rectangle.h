#pragma once
#include "object.h"

class Rect : public object
{
public:
	using object::object;
	~Rect() = default;
	void draw(SDL_Renderer* renderer, bool onlyOutline) override;
private:

};
