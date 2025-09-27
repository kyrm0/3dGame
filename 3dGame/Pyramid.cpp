#include "Pyramid.h"

Pyramid::Pyramid(double scale, double x, double y, int id)
	:Object3d(scale, x, y, id), edges()
{
	model = {
	{0, 1, 0},   // apex (top)
	{-1, 0, -1}, // base back-left
	{1, 0, -1},  // base back-right
	{1, 0, 1},   // base front-right
	{-1, 0, 1}   // base front-left
	};
	int edges[8][2] = {
		{1, 2}, {2, 3}, {3, 4}, {4, 1}, // base square
		{0, 1}, {0, 2}, {0, 3}, {0, 4}  // sides to apex
	};
	
	for (int i = 0; i < 8; i++) {
		edges[i][0] = edges[i][0];
		edges[i][1] = edges[i][1];
	}
	scratch.resize(model.size());
}
