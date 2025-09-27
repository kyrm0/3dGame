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
	SDL_SetRenderDrawColor(r, color.r, color.g, color.b, color.a);
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
