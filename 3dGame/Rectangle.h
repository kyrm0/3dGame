#pragma once
#include "object.h"

class Rectangle : public object
{
public:
	Rectangle(float x, float y, int w, int h, SDL_Color color, int id);
	~Rectangle() = default;
	void draw(SDL_Renderer* renderer) override;
private:

};
