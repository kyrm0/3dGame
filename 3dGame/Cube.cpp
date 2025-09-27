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

	double R[3][3];

	makeIdentity(R);

	rotXYZ(ax, ay, az, R);

	for (size_t i = 0; i < model.size(); ++i) {
		Vector3 v = mul(R, model[i]); /*model[i];*/ // rotate
		v.x *= scale; v.y *= scale; v.z *= scale; // convert to world space
		scratch[i] = project(v, x, y, fov, zcam, perspective); // project to 2D
	}

	for (int i = 0; i < 12; ++i) {
		const Vector3& a = scratch[edges[i][0]]; // start vertex
		const Vector3& b = scratch[edges[i][1]]; // end vertex
		SDL_RenderLine(r,
			(int)std::lround(a.x), (int)std::lround(a.y),
			(int)std::lround(b.x), (int)std::lround(b.y));
	}
}