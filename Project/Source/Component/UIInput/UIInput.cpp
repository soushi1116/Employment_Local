#include "DxLib.h"
#include "UIInput.h"
#include "../../Input/Input.h"
#include "../GameObject.h"

UIInput::UIInput(GameObject* owner) 
	: Component(owner)
{

}

UIInput::~UIInput()
{

}

void UIInput::Start()
{
	m_Owner->AddTag(TAG_UI_INPUT);
}

void UIInput::Step()
{
	if (Input::IsLeftStickInput(Input::STICK_L_UP))
	{
		m_UIInput = CURSOR_UP;
	}
	else if (Input::IsLeftStickInput(Input::STICK_L_DOWN))
	{
		m_UIInput = CURSOR_DOWN;
	}
	else if (Input::IsLeftStickInput(Input::STICK_L_RIGHT))
	{
		m_UIInput = CURSOR_RIGHT;
	}
	else if (Input::IsLeftStickInput(Input::STICK_L_LEFT))
	{
		m_UIInput = CURSOR_LEFT;
	}
	else
	{
		m_UIInput = UI_INPUT_NONE;
	}

	if (Input::IsTriggerButton(Input::BUTTON_B))
	{
		m_UITrigger = INPUT_SELECT;
	}
	else if (Input::IsTriggerButton(Input::BUTTON_A))
	{
		m_UITrigger = INPUT_CANCEL;
	}
	else
	{
		m_UITrigger = UI_TRIGGER_NONE;
	}
}
