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

private:
	std::array<std::array<int, 2>, 12> edges;

	static void makeIdentity(double R[3][3]);
	static Vector3 mul(const double m[3][3], const Vector3& v);
	static void rotXYZ(double ax, double ay, double az, double R[3][3]);
};

