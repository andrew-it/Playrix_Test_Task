#include "FVector3.h"

FVector3::FVector3(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
	
	normalize();
}

FVector3::FVector3()
{
	x = 1;
	y = 1;
	z = 1;
	
	normalize();
}

FVector3::~FVector3()
{
	printf("~FVector3");
}

void FVector3::normalize()
{
	float length = math::sqrt(x*x + y*y + z*z);
	
	x = x / length;
	y = y / length;
	z = z / length;
}

void FVector3::setValues(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

void FVector3::reverseX()
{
	x = -x;
}

void FVector3::reverseY()
{
	y = -y;
}

void FVector3::reverseZ()
{
	z = -z;
}

float FVector3::getX()
{
	return x;
}

float FVector3::getY()
{
	return y;
}

float FVector3::getZ()
{
	return z;
}
