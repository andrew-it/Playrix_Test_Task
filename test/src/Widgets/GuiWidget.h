#pragma once


///
/// Виджет - основной визуальный элемент на экране.
/// Он отрисовывает себя, а также может содержать другие виджеты.
///
class GuiWidget : public GUI::Widget
{
public:
	GuiWidget(const std::string& name, rapidxml::xml_node<>* elem);
	
	void Draw() override;
	void Update(float dt) override;
	
	void AcceptMessage(const Message& message) override;
	
	bool MouseDown(const IPoint& mouse_pos) override;
	void MouseMove(const IPoint& mouse_pos) override;
	void MouseUp(const IPoint& mouse_pos) override;
	
	void KeyPressed(int keyCode) override;
	void CharPressed(int unicodeChar) override;
	
private:
	void Init();
	
private:
	float _timer;
	float _hud_width;
	
	Render::Texture* _tex1;
	Render::Texture* _hud;
};
