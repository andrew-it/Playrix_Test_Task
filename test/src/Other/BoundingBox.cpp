#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
	BoundingBox(0, 0, 0, 0, 0, 0);
}

BoundingBox::~BoundingBox()
{
	delete(pivot);
}

BoundingBox::BoundingBox(float x, float y, float z, float _x_length, float _y_height, float _z_width)
{
	pivot = new FPoint3(x, y, z);
	setBox(_x_length, _y_height, _z_width);
}

void BoundingBox::setPoint(float x, float y, float z)
{
	pivot->setX(x);
	pivot->setY(y);
	pivot->setZ(z);
}

void BoundingBox::setPoint(FPoint3* _point)
{
	pivot = _point;
}

void BoundingBox::setBox(float _x_length, float _y_height, float _z_width)
{
	x_length = _x_length;
	y_height = _y_height;
	z_width = _z_width;
}

FPoint3* BoundingBox::getPoint()
{
	return pivot;
}
