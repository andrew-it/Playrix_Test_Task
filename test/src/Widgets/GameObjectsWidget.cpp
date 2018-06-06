#include "../../src/stdafx.h"
#include "GameObjectsWidget.h"
#include "TestAppDelegate.h"
#include "../Other/FPoint3.h"
#include "../Other/FVector3.h"

GameObjectsWidget::GameObjectsWidget(const std::string& name, rapidxml::xml_node<>* elem)
: Widget(name)
, _curTex(0)
, _timer(0)
, _angle(0)
, _max_time(50)
, _scale(0.f)
{
	Init();
}

void GameObjectsWidget::Init()
{
	_curTex = 0;
	_angle = 0;
	_timer = 0;
	
	_isGameOver = false;
	
	number_of_targets = 10;
	_max_time = 50;
	
	wallTextureName = "Wall";
	floorTextureName = "Wall";
	ceilTextureName = "Wall";
	tirWallTextureName = "Wall";
	
	wallTexture = Core::resourceManager.Get<Render::Texture>(wallTextureName);
	floorTexture = Core::resourceManager.Get<Render::Texture>(floorTextureName);
	ceilTexture = Core::resourceManager.Get<Render::Texture>(ceilTextureName);
	tirWallTexture = Core::resourceManager.Get<Render::Texture>(tirWallTextureName);
	
	for(int t = 0; t < number_of_targets; t++)
	{
		float z = TIR_DEPTH - float(t) / float(number_of_targets) * TIR_DEPTH;
		list_of_targets.push_back(std::make_shared<Target>(Target(z)));
	}
}

void GameObjectsWidget::DrawTargets()
{
	for(std::list<std::shared_ptr<Target>>::iterator iterator = list_of_targets.begin(), end = list_of_targets.end(); iterator != end; ++iterator)
	{
		(*iterator)->Draw();
	}
}

void GameObjectsWidget::UpdateTargets(float dt)
{
	for(std::list<std::shared_ptr<Target>>::iterator iterator = list_of_targets.begin(), end = list_of_targets.end(); iterator != end; ++iterator)
	{
		(*iterator)->Update(dt);
	}
}

void GameObjectsWidget::DrawBullets()
{
	for(std::list<std::shared_ptr<Bullet>>::iterator iterator = list_of_bullets.begin(), end = list_of_bullets.end(); iterator != end; ++iterator)
	{
		(*iterator)->Draw();
	}
}

void GameObjectsWidget::UpdateBullets(float dt)
{
	for(std::list<std::shared_ptr<Bullet>>::iterator iterator = list_of_bullets.begin(), end = list_of_bullets.end(); iterator != end; ++iterator)
	{
		(*iterator)->Update(dt);
	}
}

void GameObjectsWidget::checkTargets()
{
	for(std::list<std::shared_ptr<Target>>::iterator target = list_of_targets.begin(), end = list_of_targets.end(); target != end; ++target)
	{
		// === Check collision betwen bullet and target ===
		for(std::list<std::shared_ptr<Target>>::iterator target = list_of_targets.begin(), end = list_of_targets.end(); target != end; ++target)
		{
			// target point
			FPoint3* tp = (*target)->getBoundingBox()->getPoint();
			// target x, y, z sizes
			float txs = (*target)->getBoundingBox()->x_length;
			float tys = (*target)->getBoundingBox()->y_height;
			float tzs = (*target)->getBoundingBox()->z_width;
			for(std::list<std::shared_ptr<Bullet>>::iterator bullet = list_of_bullets.begin(), end = list_of_bullets.end(); bullet != end; ++bullet)
			{
				FPoint3* bp = (*bullet)->getBoundingBox()->getPoint();
				
				float bxs = (*bullet)->getBoundingBox()->x_length;
				float bys = (*bullet)->getBoundingBox()->y_height;
				float bzs = (*bullet)->getBoundingBox()->z_width;
				
				
				if (
					((tp->x >= bp->x && tp->x <= bp->x + bxs) || (tp->x + txs >= bp->x && tp->x + txs <= bp->x + bxs)) &&
					((tp->y >= bp->y && tp->y <= bp->y + bys) || (tp->y + tys >= bp->y && tp->y + tys <= bp->y + bys)) &&
					((tp->z >= bp->z && tp->z <= bp->z + bzs) || (tp->z + tzs >= bp->z && tp->z + tzs <= bp->z + bzs))
					)
				{
					(*target)->to_delete = true;
					
					(*bullet)->to_delete = true;
					(*bullet)->is_missed = false;
					(*bullet)->drawHitEffect();
				}
			}
		}
		
		// === Delete the target if it was hit ===
		if ((*target)->to_delete)
		{
			target = list_of_targets.erase(target);
		}
	}
}

void GameObjectsWidget::checkBullets()
{
	for(std::list<std::shared_ptr<Bullet>>::iterator iterator = list_of_bullets.begin(), end = list_of_bullets.end(); iterator != end; ++iterator)
	{
		if ((*iterator)->to_delete)
		{
			iterator = list_of_bullets.erase(iterator);
		}
	}
}

void GameObjectsWidget::DrawRoom()
{
	Render::device.PushMatrix();
	
	IRect texRect = wallTexture->getBitmapRect();
	
	float offset_x = (float)(WINDOW_WIDTH - TIR_WALL_LENGTH) / 2;
	float offset_y = (float)(WINDOW_HEIGHT - TIR_WALL_HEIGTH) / 2;
	
	FRect rect(texRect);
	FRect uv(0, 1, 0, 1);
	
	wallTexture->TranslateUV(rect, uv);
	
	Render::device.MatrixTranslate(offset_x, offset_y, TIR_DEPTH);
	Render::device.MatrixRotate(math::Vector3(0,0,1), 40);
	
	wallTexture->Bind();
	
	Render::DrawQuad(rect, uv);
	
	Render::device.PopMatrix();
}

void GameObjectsWidget::Draw()
{
	if (_isGameOver)
	{
		showGameOver();
	}
	DrawRoom();
	DrawTargets();
	DrawBullets();
	
	Render::BindFont("doom");
	Render::PrintString(WINDOW_WIDTH/2, WINDOW_HEIGHT - 50, "Your score: " + utils::lexical_cast(number_of_targets-list_of_targets.size()) + " / " + utils::lexical_cast(number_of_targets), 1.f, CenterAlign);
	Render::PrintString(WINDOW_WIDTH/2, WINDOW_HEIGHT - 100, "Remaining time: " + utils::lexical_cast(int(_max_time-_timer)) + "sec", 1.f, CenterAlign);
}

void GameObjectsWidget::Update(float dt)
{
	
	if (_timer > _max_time || list_of_targets.size() == 0)
	{
		_isGameOver = true;
	}
	else
	{
		_timer += dt;
		UpdateBullets(dt);
		checkBullets();
		UpdateTargets(dt);
		checkTargets();
	}
}

void GameObjectsWidget::showGameOver()
{
	Render::BindFont("doom");
	Render::PrintString(WINDOW_WIDTH/2, WINDOW_HEIGHT/3, "Press 'R' to restart.", 1.f, CenterAlign);
}

bool GameObjectsWidget::MouseDown(const IPoint &mouse_pos)
{
	if (Core::mainInput.GetMouseLeftButton())
	{
		IPoint mouse_pos = Core::mainInput.GetMousePos();
		FVector3* vector = new FVector3(mouse_pos.x - (WINDOW_WIDTH/2),
										mouse_pos.y - (WINDOW_HEIGHT/2),
										TIR_DEPTH);
		FPoint3* point = new FPoint3(TIR_WALL_LENGTH / 2, TIR_WALL_HEIGTH / 2, 1);
		makeShot(vector, point);
	}
	return false;
}

void GameObjectsWidget::restartGame()
{
	list_of_bullets.clear();
	list_of_targets.clear();
	Init();
}

void GameObjectsWidget::makeShot(FVector3* vector, FPoint3* point)
{
	list_of_bullets.push_back(std::make_shared<Bullet>(Bullet(point, vector, BULLET_SPEED)));
}

void GameObjectsWidget::AcceptMessage(const Message& message)
{
	//
	// Виджету могут посылаться сообщения с параметрами.
	//
	
	const std::string& publisher = message.getPublisher();
	const std::string& data = message.getData();
}

void GameObjectsWidget::KeyPressed(int keyCode)
{
	//
	// keyCode - виртуальный код клавиши.
	// В качестве значений для проверки нужно использовать константы VK_.
	//
	
	if (keyCode == VK_A) {
		// Реакция на нажатие кнопки A
		// restartGame();
	}
}

void GameObjectsWidget::CharPressed(int unicodeChar)
{
	//
	// unicodeChar - Unicode код введённого символа
	//
	
	if (unicodeChar == L'r') {
		restartGame();
	}
}
