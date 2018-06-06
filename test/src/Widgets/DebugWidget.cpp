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
		//
		// Получаем текущее положение курсора мыши.
		//
		IPoint mouse_pos = Core::mainInput.GetMousePos();
		
		//
		// Этот вызов отключает текстурирование при отрисовке.
		//
		Render::device.SetTexturing(false);
		
		//
		// Метод BeginColor() проталкивает в стек текущий цвет вершин и устанавливает новый.
		//
		Render::BeginColor(Color(255, 128, 0, 255));
		
		//
		// Метод DrawRect() выводит в графическое устройство квадратный спрайт, состоящий их двух
		// примитивов - треугольников, используя при этом текущий цвет для вершин и привязанную (binded) текстуру,
		// если разрешено текстурирование.
		//
		// Перед вызовом DrawRect() должен быть вызов Texture::Bind(), либо SetTexturing(false),
		// иначе визуальный результат будет непредсказуемым.
		//
		Render::DrawRect(WINDOW_WIDTH - 150, 0, 150, 50);
		
		//
		// Метод EndColor() снимает со стека текущий цвет вершин, восстанавливая прежний.
		//
		Render::EndColor();
		
		//
		// Опять включаем текстурирование.
		//
		Render::device.SetTexturing(true);
		
		
		Render::BindFont("doom");
		Render::PrintString(WINDOW_WIDTH - 75, 35, utils::lexical_cast(mouse_pos.x) + ", " + utils::lexical_cast(mouse_pos.y), 1.f, CenterAlign);
	}
}

