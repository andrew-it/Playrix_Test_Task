#pragma once
#include "../Other/BoundingBox.h"
#include "../Other/IUpdatable.h"
#include "../Other/IDrawable.h"
#include "../Other/IInitable.h"
#include "../Other/FPoint3.h"

/**
 * Abstract class IGameObject.
 * Base for Billet and Target classes.
 */
using namespace std;

class IGameObject: public IUpdatable, public IDrawable, public IInitable
{
public:
	BoundingBox* box;
	bool to_delete;
	
protected:
	Render::Texture* texture;
	float _timer;
	FPoint offset;
	EffectsContainer _effCont;

public:
	IGameObject();
	virtual ~IGameObject();
	
	void Draw() override;
	virtual bool collision(IGameObject* collisionWith);
	virtual BoundingBox* getBoundingBox();
	virtual void drawEffect(std::string effectName);
	
	virtual FPoint3 mapTo2d();
	
private:
	float getScale();
	float getDepthScale();
};
