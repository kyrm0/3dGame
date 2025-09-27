#include "Cube.h"

Cube::Cube(double scale, double cx, double cy) 
	:scale(scale), cx(cx), cy(cy), ax(0), ay(0), az(0)
{
	model = {
		{-1,  1,  1}, { 1,  1,  1}, { 1, -1,  1}, {-1, -1,  1}, // front square z=+1
		{-1,  1, -1}, { 1,  1, -1}, { 1, -1, -1}, {-1, -1, -1} // back square z=-1
	};

	int e[12][2] = {
		{0,1},{1,2},{2,3},{3,0}, //front square lines
		{4,5},{5,6},{6,7},{7,4}, //back square lines
		{0,4},{1,5},{2,6},{3,7} // connector lines
	};

	// copy to edges from e
	for (int i = 0; i < 12; i++) {
		edges[i][0] = e[i][0];
		edges[i][1] = e[i][1];
	}
	// resize scratch to fit model size
	scratch.resize(model.size());
}

void Cube::update(double dax, double day, double daz)
{
	ax += dax;
	ay += day;
	az += daz;
}

void Cube::draw(SDL_Renderer* r, bool perspective, double fov, double zcam) const
{
	SDL_SetRenderDrawColor(r, 0, 0, 0, 255);

	double R[3][3];

	makeIdentity(R);

	rotXYZ(ax, ay, az, R);

	for (size_t i = 0; i < model.size(); ++i) {
		Vector3 v = mul(R, model[i]); /*model[i];*/ // rotate
		v.x *= scale; v.y *= scale; v.z *= scale; // convert to world space
		scratch[i] = project(v, cx, cy, fov, zcam, perspective); // project to 2D
	}

	for (int i = 0; i < 12; ++i) {
		const Vector3& a = scratch[edges[i][0]]; // start vertex
		const Vector3& b = scratch[edges[i][1]]; // end vertex
		SDL_RenderLine(r,
			(int)std::lround(a.x), (int)std::lround(a.y),
			(int)std::lround(b.x), (int)std::lround(b.y));
	}
}

Vector2 Cube::getPos()
{
	return {cx, cy};
}

void Cube::updatePos(Vector2 newPos)
{
	cx = newPos.x;
	cy = newPos.y;
}

void Cube::scaleBy(double dScale)
{
	this->scale += dScale;
}

void Cube::updScale(double newScale)
{
	this->scale = newScale;
}

void Cube::makeIdentity(double R[3][3])
{
	R[0][0] = 1; R[0][1] = 0; R[0][2] = 0;
	R[1][0] = 0; R[1][1] = 1; R[1][2] = 0;
	R[2][0] = 0; R[2][1] = 0; R[2][2] = 1;
}

Vector3 Cube::mul(const double m[3][3], const Vector3& v)
{
	return {
		m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
		m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
		m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z
	};
}

void Cube::rotXYZ(double ax, double ay, double az, double R[3][3])
{
	double cx = std::cos(ax), sx = std::sin(ax);
	double cy = std::cos(ay), sy = std::sin(ay);
	double cz = std::cos(az), sz = std::sin(az);
	double Rx[3][3] = { {1,0,0},{0,cx,-sx},{0,sx,cx} };
	double Ry[3][3] = { {cy,0,sy},{0,1,0},{-sy,0,cy} };
	double Rz[3][3] = { {cz,-sz,0},{sz,cz,0},{0,0,1} };
	// T1 = Rz * Ry
	double T1[3][3]{};
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)
		T1[i][j] = Rz[i][0] * Ry[0][j] + Rz[i][1] * Ry[1][j] + Rz[i][2] * Ry[2][j];
	// R = T1 * Rx
	for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++)
		R[i][j] = T1[i][0] * Rx[0][j] + T1[i][1] * Rx[1][j] + T1[i][2] * Rx[2][j];
}

Vector3 Cube::project(const Vector3& v, double cx, double cy, double fov, double zcam, bool perspective)
{
	if (!perspective) {
		return { v.x + cx, v.y + cy, v.z };
	}
	double z = v.z + zcam;
	double invz = z != 0 ? 1.0/ z : 0.0;
	
	return { v.x * fov * invz + cx, v.y * fov * invz + cy, z };

}
