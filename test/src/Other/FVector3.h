#pragma once

class FVector3
{
protected:
	float x, y, z;

public:
	FVector3(float x, float y, float z);
	FVector3();
	~FVector3();
	
	void setValues(float x, float y, float z);
	
	void normalize();
	
	void reverseX();
	void reverseY();
	void reverseZ();
	
	float getX();
	float getY();
	float getZ();
	
};
