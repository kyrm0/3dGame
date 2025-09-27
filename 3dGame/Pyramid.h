#pragma once
#include "Object3d.h"

class Pyramid : public Object3d
{
public:
	Pyramid(double scale, double x, double y, int id);

	void draw(SDL_Renderer* r, bool perspective, double fov, double zcam, SDL_Color color) const override;

	const std::vector<std::array<int, 2>>& getEdges() const override { return edges; }

private:
	std::vector<std::array<int, 2>> edges;
};

