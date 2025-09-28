#include "Cube.h"

Cube::Cube(double scale, double cx, double cy, int id)
	:Object3d(scale, cx, cy, id), edges()
{
	model = {
		{-1,  1,  1}, { 1,  1,  1}, { 1, -1,  1}, {-1, -1,  1}, // front square z=+1
		{-1,  1, -1}, { 1,  1, -1}, { 1, -1, -1}, {-1, -1, -1} // back square z=-1
	};

	edges = {
		{0,1},{1,2},{2,3},{3,0}, //front square lines
		{4,5},{5,6},{6,7},{7,4}, //back square lines
		{0,4},{1,5},{2,6},{3,7} // connector lines
	};
	// resize scratch to fit model size
	scratch.resize(model.size());
}

void Cube::draw(SDL_Renderer* r, bool perspective, double fov, double zcam, SDL_Color color) const
{
	Object3d::draw(r, perspective, fov, zcam, color);

	
}