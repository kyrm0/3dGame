#include "Points.h"

Points::Points()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Points::Points(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Points::Points(double x, double y)
{
	this->x = x;
	this->y = y;
	this->z = 0;
}

double Points::operator[](int index) const
{
	if (index == 0) return this->x;
	if (index == 1) return this->y;
	return this->z;
}

double& Points::operator[](int index)
{
	if (index == 0) return this->x;
	if (index == 1) return this->y;
	return this->z;
}
