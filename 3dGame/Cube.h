#pragma once
#include <SDL3/SDL.h>
#include <vector>
#include <cmath>

struct Vector3
{
	double x, y, z;
};

class Cube
{
public:
	Cube(double scale, double cx, double cy);

	void update(double dax, double day, double daz);
	void draw(SDL_Renderer* r, bool perspective=false, double fov=600.0, double zcam = 5.0) const;

private:
	std::vector<Vector3> model;
	int edges[12][2];
	double scale, cx, cy;
	mutable std::vector<Vector3> scratch; // transformed vertices
	double ax, ay, az;

	static Vector3 mul(const double m[3][3], const Vector3& v);
	static void rotXYZ(double ax, double ay, double az, double R[3][3]);
	static Vector3 project(const Vector3& v, double cx, double cy, double fov, double zcam, bool perspective);
};

