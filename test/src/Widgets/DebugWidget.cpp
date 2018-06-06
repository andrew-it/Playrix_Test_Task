#include "../../src/stdafx.h"
#include "DebugWidget.h"
#include "TestAppDelegate.h"
#include "../General/Constants.h"

/**
 * Widget для отображения отладочной информации
 */

DebugWidget::DebugWidget(const std::string& name, rapidxml::xml_node<>* elem)
: Widget(name)
{
}

void DebugWidget::Draw()
{
	if (DEBUG_ON)
	{
		IPoint mouse_pos = Core::mainInput.GetMousePos();
		Render::device.SetTexturing(false);
		Render::BeginColor(Color(255, 128, 0, 255));
		Render::DrawRect(WINDOW_WIDTH - 150, 0, 150, 50);
		Render::EndColor();
		Render::device.SetTexturing(true);
		Render::BindFont("doom");
		Render::PrintString(WINDOW_WIDTH - 75, 35, utils::lexical_cast(mouse_pos.x) + ", " + utils::lexical_cast(mouse_pos.y), 1.f, CenterAlign);
	}
}

