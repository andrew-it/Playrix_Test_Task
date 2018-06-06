#include "Bullet.h"
#include "../General/Constants.h"

Bullet::Bullet(FPoint3* point, FVector3* _vector, float _speed)
{
	vector = _vector;
	speed = _speed;
	box->setPoint(point);
	Init();
}

Bullet::~Bullet()
{
	printf("~Bullet\n");
}

void Bullet::Update(float dt)
{
	if (!to_delete)
	{
		// === Move the bullet in 3d ===
		box->setPoint(box->getPoint()->getX() + vector->getX() * speed * dt,
					  box->getPoint()->getY() + vector->getY() * speed * dt,
					  box->getPoint()->getZ() + vector->getZ() * speed * dt);
		
		// === Calculate collisiions and ricochet ===
		collisionWithWalls();
		
		// === Update the effects container ===
		_effCont.Update(dt);
		
		// === Update trace position ===
		FPoint3 pointOnScreen = mapTo2d();
		_trace->posX = pointOnScreen.getX();
		_trace->posY = pointOnScreen.getY();
	}
}

void Bullet::Init()
{
	box->setBox(BULLET_WIDTH, BULLET_HEIGHT, speed*2);
	texture = Core::resourceManager.Get<Render::Texture>("Bullet");
	is_missed = false;
	
	_bloodEffectName = "FindItem2";
	_traceEffectName = "Iskra";
	_splashEffectName = "FindItem2";
	
	_trace = _effCont.AddEffect(_traceEffectName);
}

void Bullet::drawHitEffect()
{
	drawEffect(_bloodEffectName);
}

bool Bullet::collisionWithWalls()
{
	float depth_scale = 1.0f - box->getPoint()->getZ() / TIR_DEPTH;
	// === Collision by x ===
	if (box->getPoint()->getX() < 0 || box->getPoint()->getX() > TIR_WALL_HEIGTH)
	{
		box->getPoint()->setX((int)box->getPoint()->getX());
		vector->reverseX();
		drawEffect(_splashEffectName);
		//		printf("X collision: x: %f; y: %f; z: %f;\n", box->getPoint()->getX(), box->getPoint()->getY(), box->getPoint()->getZ());
		return true;
	}
	
	// === Collision by y ===
	if (box->getPoint()->getY() < 0 || box->getPoint()->getY() > TIR_WALL_HEIGTH)
	{
		box->getPoint()->setY((int)box->getPoint()->getY());
		vector->reverseY();
		drawEffect(_splashEffectName);
		//		printf("Y collision: x: %f; y: %f; z: %f;\n", box->getPoint()->getX(), box->getPoint()->getY(), box->getPoint()->getZ());
		return true;
	}
	
	// === Collision by z ===
	if (box->getPoint()->getZ() < 0 || box->getPoint()->getZ() > TIR_DEPTH)
	{
		if (!to_delete)
			drawEffect(_splashEffectName);
		is_missed = true;
		printf("Miss\n");
		to_delete = true;
		_trace->Finish();
		//		printf("Z collision: x: %f; y: %f; z: %f;\n", box->getPoint()->getX(), box->getPoint()->getY(), box->getPoint()->getZ());
	}
	
	return false;
}
