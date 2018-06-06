#pragma once

class DebugWidget : public GUI::Widget
{
public:
	DebugWidget(const std::string& name, rapidxml::xml_node<>* elem);
	
	void Draw() override;
};
