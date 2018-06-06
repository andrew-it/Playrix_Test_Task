#pragma once

class FPoint3
{
public:
	float x, y, z;

public:
	FPoint3();
	FPoint3(float x, float y, float z);
	~FPoint3();
	
	FPoint3 operator - () const;
	FPoint3& operator += (const FPoint3& p);
	FPoint3& operator -= (const FPoint3& p);
	
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	
	float getX();
	float getY();
	float getZ();
};
