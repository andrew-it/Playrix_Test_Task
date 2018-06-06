#pragma once
#include "FPoint3.h"

class BoundingBox
{
public:
	FPoint3* pivot;
	float x_length, z_width, y_height;
	
public:
	BoundingBox();
	BoundingBox(float x, float y, float z, float x_length, float z_width, float y_height);
	virtual ~BoundingBox();
	
	void setPoint(float x, float y, float z);
	void setPoint(FPoint3* point);
	FPoint3* getPoint();
	
	void setBox(float x_length, float y_height, float z_width);
};
