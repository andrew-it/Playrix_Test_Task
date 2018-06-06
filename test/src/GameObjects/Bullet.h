#pragma once

#include "IGameObject.h"
#include "../Other/IProjectile.h"
#include "../Other/FVector3.h"
#include "../Other/FPoint3.h"

using namespace std;

class Bullet: public IGameObject, public IProjectile
{
public:
	float speed;
	FVector3* vector;
	bool is_missed;
private:
	ParticleEffectPtr _blood;
	ParticleEffectPtr _splash;
	ParticleEffectPtr _trace;
	
	std::string _bloodEffectName;
	std::string _traceEffectName;
	std::string _splashEffectName;
	
public:
	Bullet(FPoint3* point, FVector3* vector, float speed);
	~Bullet();
	
	void Update(float dt) override;
	void Init() override;
	
	void drawHitEffect();
	
protected:
	bool collisionWithWalls();
};
