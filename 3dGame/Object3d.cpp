#include "Object3d.h"

std::vector<std::unique_ptr<Object3d>> Object3d::objects{};
std::unordered_map<int, size_t> Object3d::ixById{};


Object3d::Object3d(double scale, double x, double y, int id)
	:scale(scale), x(x), y(y), id_(id), model(), scratch(), ax(0), ay(0), az(0) {}

void Object3d::update(double dax, double day, double daz)
{
	ax += dax;
	ay += day;
	az += daz;
}

void Object3d::draw(SDL_Renderer* r, bool perspective=false, double fov=600.0, double zcam=5.0, SDL_Color color={0,0,0,255}) const
{

	const auto& e = getEdges();
	SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);

	double R[3][3];
	makeIdentity(R);
	rotXYZ(ax, ay, az, R);

	for (size_t i = 0; i < model.size(); ++i) {
		Vector3 v = mul(R, model[i]); /*model[i];*/ // rotate
		v.x *= scale; v.y *= scale; v.z *= scale; // convert to world space
		scratch[i] = project(v, x, y, fov, zcam, perspective); // project to 2D
	}

	for (int i = 0; i < e.size(); ++i) {
		const Vector3& a = scratch[e[i][0]]; // start vertex
		const Vector3& b = scratch[e[i][1]]; // end vertex
		SDL_RenderLine(r,
			(int)std::lround(a.x), (int)std::lround(a.y),
			(int)std::lround(b.x), (int)std::lround(b.y));
	}
}

void Object3d::add(std::unique_ptr<Object3d>&& o)
{
	const int id = o->id_;
	if (ixById.count(id)) return;
	const size_t idx = objects.size();
	ixById[id] = idx;
	objects.emplace_back(std::move(o));
}

Object3d* Object3d::getObjectById(int id)
{
	auto it = ixById.find(id);
	if (it == ixById.end()) return nullptr;
	return objects[it->second].get();
}

void Object3d::drawObjects(SDL_Renderer* r)
{
	for (auto& obj : objects) if (obj) obj->draw(r);
}

void Object3d::scaleBy(double dScale)
{
	scale += dScale;
}

void Object3d::updScale(double newScale)
{
	scale = newScale;
}

Vector3 Object3d::project(const Vector3& v, double cx, double cy, double fov, double zcam, bool perspective)
{
	if (!perspective) {
		return { v.x + cx, v.y + cy, v.z };
	}
	double z = v.z + zcam;
	double invz = z != 0 ? 1.0 / z : 0.0;

	return { v.x * fov * invz + cx, v.y * fov * invz + cy, z };
}

Vector3 Object3d::mul(const double m[3][3], const Vector3& v)
{
	return {
		m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
		m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
		m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z
	};
}

void Object3d::rotXYZ(double ax, double ay, double az, double R[3][3])
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

void Object3d::makeIdentity(double R[3][3])
{
	R[0][0] = 1; R[0][1] = 0; R[0][2] = 0;
	R[1][0] = 0; R[1][1] = 1; R[1][2] = 0;
	R[2][0] = 0; R[2][1] = 0; R[2][2] = 1;
}
