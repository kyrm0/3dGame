#pragma once
#include <vector>

class Points
{
public:
	Points();
	Points(double x, double y, double z);
	Points(double x, double y);
	double operator[](int index) const;
	double& operator[](int index);
	~Points() = default;

private:
	double x, y, z;
};

typedef std::vector<double> Vector;
typedef std::vector<Vector> Matrix;