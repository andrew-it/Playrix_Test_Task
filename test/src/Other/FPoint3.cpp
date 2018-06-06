#include "FPoint3.h"

FPoint3::FPoint3()
{
	x = y = z = 0;
}

FPoint3::FPoint3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

FPoint3::~FPoint3()
{
//	printf("~FPoint3\n");
}

FPoint3 operator + (const FPoint3& a, const FPoint3& b)
{
	return FPoint3(a.x + b.x, a.y + b.y, a.z + b.z);
}

FPoint3 operator - (const FPoint3& a, const FPoint3& b)
{
	return FPoint3(a.x - b.x, a.y - b.y, a.z - b.z);
}

bool operator == (const FPoint3& a, const FPoint3& b)
{
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

bool operator != (const FPoint3& a, const FPoint3& b)
{
	return a.x != b.x || a.y != b.y || a.z != b.z;
}

void FPoint3::setX(float _x)
{
	x = _x;
}

void FPoint3::setY(float _y)
{
	y = _y;
}

void FPoint3::setZ(float _z)
{
	z = _z;
}

float FPoint3::getX()
{
	return x;
}

float FPoint3::getY()
{
	return y;
}

float FPoint3::getZ()
{
	return z;
}
