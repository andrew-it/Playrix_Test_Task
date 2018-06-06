#include "Target.h"
#include <cstdlib>
#include "../General/Constants.h"

Target::Target(FPoint3* point)
{
	box->setPoint(point);
	Init();
}

Target::Target()
{
	box->setPoint(getRandomPoint3InRange(TIR_WALL_LENGTH, TIR_WALL_HEIGTH, TIR_DEPTH));
	Init();
}

Target::Target(float z)
{
	box->setPoint(getRandomPoint3InRange(TIR_WALL_LENGTH-TARGET_LENGTH,
										 TIR_WALL_HEIGTH-TARGET_HEIGTH,
										 TIR_DEPTH));
	box->getPoint()->setZ(z);
	Init();
}

Target::~Target()
{
	printf("~Target\n");
}

void Target::Init()
{
	// === Set BoundingBox sizes ===
	box->x_length = TARGET_LENGTH;
	box->y_height = TARGET_HEIGTH; // Main size -- defined the size of the object in the screen
	box->z_width = 30;
	
	// === Number of points in spline ===
	number_of_points = 10;
	
	// === Define spline ===
	// First key is a spawn point
	spline.addKey(0.0f, FPoint(box->getPoint()->getX(), box->getPoint()->getY()));
	// Define spline's keys except the last one
	for(int i = 1; i < number_of_points; i++)
		spline.addKey(float(i) / float(number_of_points), this->getRandomPointInRange((float)TIR_WALL_LENGTH, (float)TIR_WALL_HEIGTH));
	// Last key is a spawn point
	spline.addKey(1.0f, FPoint(box->getPoint()->getX(), box->getPoint()->getY()));
	spline.CalculateGradient();
	
	// === Define the texture ===
	texture = Core::resourceManager.Get<Render::Texture>("Cacodemon");
}

FPoint Target::getRandomPointInRange(float x_max, float y_max)
{
	return FPoint(x_max*((float)rand() / RAND_MAX), y_max*((float)rand() / RAND_MAX));
}

FPoint3* Target::getRandomPoint3InRange(float x_max, float y_max, float z_max)
{
	return new FPoint3(x_max*((float)rand() / RAND_MAX), y_max*((float)rand() / RAND_MAX), z_max*((float)rand() / RAND_MAX));
}

void Target::Update(float dt)
{
	// === Updating timer and overflow checking ===
	_timer += dt;
	if (_timer > float(number_of_points))
		_timer = 0.0f;
	
	// === Updating position (pivot point) by spline ===
	FPoint currentPosition = spline.getGlobalFrame(math::clamp(0.0f, 1.0f, _timer / float(number_of_points)));
	box->setPoint(currentPosition.x, currentPosition.y, box->getPoint()->getZ());
	
	// === Update the effects container ===
	_effCont.Update(dt);
}

bool Target::collision(IGameObject* collisionWith)
{
	// TODO: override this function following the target shape (circle)
	return false;
}
