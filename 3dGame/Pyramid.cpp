#include "Pyramid.h"

Pyramid::Pyramid(double scale, double x, double y, int id)
	:Object3d(scale, x, y, id), edges()
{
	model = {
	{0, -1, 0},   // apex (top)
	{-1, 0, -1}, // base back-left
	{1, 0, -1},  // base back-right
	{1, 0, 1},   // base front-right
	{-1, 0, 1}   // base front-left
	};
	edges = {
		{1, 2}, {2, 3}, {3, 4}, {4, 1}, // base square
		{0, 1}, {0, 2}, {0, 3}, {0, 4}  // sides to apex
	};
	scratch.resize(model.size());
	SDL_Log("Madde pyramid at %f, %f", x, y);
}

void Pyramid::draw(SDL_Renderer* r, bool perspective, double fov, double zcam, SDL_Color color) const
{
	Object3d::draw(r, perspective, fov, zcam, color);
	double R[3][3];

	makeIdentity(R);

	rotXYZ(ax, ay, az, R);

	
}
