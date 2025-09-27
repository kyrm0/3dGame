#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include <vector>
#include <unordered_map>

#define ID_RECT1 1

class object
{
public:
	object(float x, float y, int width, int height, SDL_Color color, int id);
	virtual ~object() = default;
	virtual void draw(SDL_Renderer* renderer, bool onlyOutline) = 0; // <-- Move to public section
	static void add(std::unique_ptr<object>&& o); // Placeholder for update function
	static void drawObjects(SDL_Renderer* renderer);

	void setPos(float nx, float ny) { x = nx; y = ny; }
	void moveBy(float dx, float dy) { x += dx; y += dy; }
	std::pair<float, float> pos() const { return { x,y }; }
	bool remove(int id);
	static object* getObjectById(int id);

protected:
	float x, y;
	float width, height;
	SDL_Color color;
	int id_;
	static std::vector<std::unique_ptr<object>> objects;
	static std::unordered_map<int, size_t> ixById;
};

