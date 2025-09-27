#pragma once
#include <vector>
#include <array>
#include <SDL3/SDL.h>
#include <memory>
#include <unordered_map>

struct Vector3
{
	double x, y, z;
};

class Object3d
{
public:
	Object3d(double scale, double x, double y, int id);

	virtual void update(double dax, double day, double daz);

	virtual void draw(SDL_Renderer* r, bool perspective, double fov, double zcam, SDL_Color color) const;

	static void add(std::unique_ptr<Object3d>&& o);
	static Object3d* getObjectById(int id);
	static void drawObjects(SDL_Renderer* r);

	virtual void scaleBy(double dScale);
	virtual void updScale(double newScale);

protected:
	double scale, x, y;
	std::vector<Vector3> model;
	mutable std::vector<Vector3> scratch;
	double ax, ay, az;
	int id_;
	static std::vector<std::unique_ptr<Object3d>> objects;
	static std::unordered_map<int, size_t> ixById;

	static Vector3 project(const Vector3& v, double cx, double cy, double fov, double zcam, bool perspective);

};

