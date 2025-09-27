#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <cmath>
#include "Object3d.h"


class Cube : public Object3d
{
public:
	Cube(double scale, double cx, double cy, int id);

	void draw(SDL_Renderer* r, bool perspective=false, double fov=600.0, double zcam = 5.0, SDL_Color color = {0,0,0,255}) const override;

	const std::vector<std::array<int, 2>>& getEdges() const override { return edges; }

private:
	std::vector<std::array<int, 2>> edges;

	
};

