#pragma once
#include "../GameObjects/Target.h"
#include "../GameObjects/Bullet.h"

using namespace std;

class GameObjectsWidget : public GUI::Widget
{
public:
	GameObjectsWidget(const std::string& name, rapidxml::xml_node<>* elem);
	
	void Draw() override;
	void Update(float dt) override;
	
	bool MouseDown(const IPoint& mouse_pos) override;
	void CharPressed(int unicodeChar) override;
	
	void makeShot(FVector3* vector, FPoint3* point);
	
private:
	void Init();
	// === TODO: Да, нижеописанные функции можно было бы обобщить, но скорость написания сейчас важнее ===
	void DrawTargets();
	void DrawBullets();
	void DrawRoom();
	
	void UpdateTargets(float dt);
	void UpdateBullets(float dt);
	
	void checkTargets();
	void checkBullets();
	
	void restartGame();
	
	void showGameOver();
	
private:
	float _timer;
	float _max_time;
	float _scale;
	float _angle;
	int _curTex;
	bool _isGameOver;
	
	int number_of_targets;
	
	std::list<std::shared_ptr<Target>> list_of_targets;
	std::list<std::shared_ptr<Bullet>> list_of_bullets;
	
	std::string wallTextureName;
	std::string floorTextureName;
	std::string ceilTextureName;
	std::string tirWallTextureName;
	
	Render::Texture* wallTexture;
	Render::Texture* floorTexture;
	Render::Texture* ceilTexture;
	Render::Texture* tirWallTexture;

};
