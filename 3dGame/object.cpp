#include "object.h"
#include "Rectangle.h"



std::vector<std::unique_ptr<object>> object::objects{};
std::unordered_map<int, size_t> object::ixById{};

object::object(float x=0, float y=0, int width=0, int height=0, SDL_Color color={0,0,0}, int id=0)
	: x(x), y(y), width(width), height(height), color(color), id_(id) {}

void object::draw(SDL_Renderer* renderer, bool onlyOutline)
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void object::add(std::unique_ptr<object>&& o)
{
	const int id = o->id_;
	if (ixById.count(id)) return;
	const size_t idx = objects.size();
	ixById[id] = idx;
	objects.emplace_back(std::move(o));
}



void object::drawObjects(SDL_Renderer* renderer)
{
	for (auto& obj : objects) if (obj) obj->draw(renderer, false);

	
}

bool object::remove(int id)
{
	auto it = ixById.find(id);
	if (it == ixById.end()) return false;

	size_t i = it->second;
	size_t last = objects.size() - 1;

	if (i != last) {
		std::swap(objects[i], objects[last]);           // move last into i
		ixById[objects[i]->id_] = i;                    // fix moved id index
	}
	objects.pop_back();
	ixById.erase(it);
	return true;

}

object* object::getObjectById(int id)
{
	auto it = ixById.find(id);
	if (it == ixById.end()) return nullptr;
	return objects[it->second].get();
}
