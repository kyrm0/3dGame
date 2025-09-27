#pragma once
#include "Object3d.h"

class Pyramid : Object3d
{
public:
	Pyramid(double scale, double x, double y, int id);

private:
	std::array<std::array < int, 2>, 8> edges;
};

