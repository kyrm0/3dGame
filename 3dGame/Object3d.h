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

	virtual ~Object3d() = default;

	virtual void update(double dax, double day, double daz);

	virtual void draw(SDL_Renderer* r, bool perspective, double fov, double zcam, SDL_Color color) const;

	static void add(std::unique_ptr<Object3d>&& o);
	static Object3d* getObjectById(int id);
	static void drawObjects(SDL_Renderer* r);

	virtual void scaleBy(double dScale);
	virtual void updScale(double newScale);

	virtual const std::vector<std::array<int, 2>>& getEdges() const = 0;

protected:
	double scale, x, y;
	std::vector<Vector3> model;
	mutable std::vector<Vector3> scratch;
	double ax, ay, az;
	int id_;
	std::vector<std::array<int, 2>> edges;



	static std::vector<std::unique_ptr<Object3d>> objects;
	static std::unordered_map<int, size_t> ixById;
	static Vector3 project(const Vector3& v, double cx, double cy, double fov, double zcam, bool perspective);
	static Vector3 mul(const double m[3][3], const Vector3& v);
    static void rotXYZ(double ax, double ay, double az, double R[3][3]);
	static void makeIdentity(double R[3][3]);
};