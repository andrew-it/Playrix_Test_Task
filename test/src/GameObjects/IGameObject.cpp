#include "IGameObject.h"
#include "../General/Constants.h"

IGameObject::IGameObject()
{
	_timer = 0;
	
	box = new BoundingBox();
	
	to_delete = false;
}

IGameObject::~IGameObject()
{
	
}


bool IGameObject::collision(IGameObject* collisionWith)
{
	return false;
}

BoundingBox* IGameObject::getBoundingBox()
{
	return box;
}

void IGameObject::Draw()
{
	// distance -- is a value of 'z' variable (with increasing of the z, the distance increase too -> the size of texture lead to decrease)
	
	// === Offset updating ===
	offset.x = (float)(WINDOW_WIDTH - TIR_WALL_LENGTH) / 2;
	offset.y = (float)(WINDOW_HEIGHT - TIR_WALL_HEIGTH) / 2;
	
	if (texture && !to_delete)
	{
		Render::device.PushMatrix();
		
		IRect texRect = texture->getBitmapRect();
		
		FRect rect(texRect);
		FRect uv(0, 1, 0, 1);
		
		texture->TranslateUV(rect, uv);
		
		FPoint3 position = mapTo2d();
		
		Render::device.MatrixTranslate(position.getX(), position.getY(), position.getZ());
		Render::device.MatrixScale(getScale());
		
		texture->Bind();
		
		Render::DrawQuad(rect, uv);
		
		Render::device.PopMatrix();
		
		_effCont.Draw();
	}
	else
	{
		// TODO: error message in DEBUG mode
	}
}

float IGameObject::getScale()
{
	float depth_scale = getDepthScale();
	float fit_texture_to_box_scale = box->y_height / texture->getBitmapRect().Height();
	return depth_scale * fit_texture_to_box_scale;
}

float IGameObject::getDepthScale()
{
	return 1.0f - box->getPoint()->getZ() / TIR_DEPTH + (float(TIR_WALL_HEIGTH) / float(WINDOW_HEIGHT));
}

void IGameObject::drawEffect(std::string effectName)
{
	if (!to_delete)
	{
		ParticleEffectPtr eff = _effCont.AddEffect(effectName);
		FPoint3 effect_position = mapTo2d();
		eff->posX = effect_position.getX() + box->x_length / 2;
		eff->posY = effect_position.getY() + box->y_height / 2;
		eff->Reset();
	}
}

FPoint3 IGameObject::mapTo2d()
{
	float _z = box->getPoint()->getZ();
	float _x = offset.x + box->getPoint()->getX();
	float _y = offset.y + box->getPoint()->getY();
	return FPoint3(_x, _y, _z);
}
