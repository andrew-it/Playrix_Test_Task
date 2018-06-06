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
	
private:
	void Init();
};
