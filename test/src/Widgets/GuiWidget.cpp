#include "../../src/stdafx.h"
#include "GuiWidget.h"
#include "TestAppDelegate.h"

GuiWidget::GuiWidget(const std::string& name, rapidxml::xml_node<>* elem)
: Widget(name)
{
	Init();
}

void GuiWidget::Init()
{
}

void GuiWidget::Draw()
{
	IPoint mouse_pos = Core::mainInput.GetMousePos();
}
