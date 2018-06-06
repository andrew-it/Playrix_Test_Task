#pragma once
#include "IGameObject.h"

class Target: public IGameObject
{
public:
	TimedSpline<FPoint> spline;
	
private:
	int number_of_points;
	
public:
	Target(FPoint3* point);
	Target(float z);
	Target();
	~Target();
	
	void Update(float dt) override;
	bool collision(IGameObject* collisionWith) override;
	
private:
	FPoint getRandomPointInRange(float x_max, float y_max);
	FPoint3* getRandomPoint3InRange(float x_max, float y_max, float z_max);
	void Init() override;
};
