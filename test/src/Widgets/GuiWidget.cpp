#include "../../src/stdafx.h"
#include "GuiWidget.h"
#include "TestAppDelegate.h"

GuiWidget::GuiWidget(const std::string& name, rapidxml::xml_node<>* elem)
: Widget(name)
, _timer(0)
, _hud_width(1.f)
{
	Init();
}

void GuiWidget::Init()
{
	_tex1 = Core::resourceManager.Get<Render::Texture>("btnStart_Text");
	_hud = Core::resourceManager.Get<Render::Texture>("hud1");
	
	_hud_width = this->getWidth();
}

void GuiWidget::Draw()
{
//	Render::device.PushMatrix();
//	IRect texRect = _hud->getBitmapRect();
//	FRect rect(texRect);
//	FRect uv(0, 1, 0, 1);
//	_hud->TranslateUV(rect, uv);
//	float _hud_scale = float(WINDOW_WIDTH) / float(texRect.Width());
//
//	Render::device.MatrixScale(_hud_scale);
//	_hud->Bind();
//	Render::DrawQuad(rect, uv);
//
//	_hud->Draw();
//	Render::device.PopMatrix();
	
	//
	// Получаем текущее положение курсора мыши.
	//
	IPoint mouse_pos = Core::mainInput.GetMousePos();
}

void GuiWidget::Update(float dt)
{
	
}

bool GuiWidget::MouseDown(const IPoint &mouse_pos)
{
	if (Core::mainInput.GetMouseRightButton())
	{

	}
	return false;
}

void GuiWidget::MouseMove(const IPoint &mouse_pos)
{

}

void GuiWidget::MouseUp(const IPoint &mouse_pos)
{

}

void GuiWidget::AcceptMessage(const Message& message)
{
	//
	// Виджету могут посылаться сообщения с параметрами.
	//
	
	const std::string& publisher = message.getPublisher();
	const std::string& data = message.getData();
}

void GuiWidget::KeyPressed(int keyCode)
{
	//
	// keyCode - виртуальный код клавиши.
	// В качестве значений для проверки нужно использовать константы VK_.
	//
	
	if (keyCode == VK_A) {
		// Реакция на нажатие кнопки A
	}
}

void GuiWidget::CharPressed(int unicodeChar)
{
	//
	// unicodeChar - Unicode код введённого символа
	//
	
	if (unicodeChar == L'а') {
		// Реакция на ввод символа 'а'
	}
}
