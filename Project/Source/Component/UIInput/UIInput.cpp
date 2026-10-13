#include "DxLib.h"
#include "UIInput.h"
#include "../../Input/Input.h"
#include "../GameObject.h"

UIInput::UIInput(GameObject* owner) : Component(owner)
{
	m_CompName = "Input";
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
	if (Input::IsLeftStickInput(Input::STICK_L_DOWN))
	{
		m_UIInput = CURSOR_DOWN;
	}
	if (Input::IsLeftStickInput(Input::STICK_L_RIGHT))
	{
		m_UIInput = CURSOR_RIGHT;
	}
	if (Input::IsLeftStickInput(Input::STICK_L_LEFT))
	{
		m_UIInput = CURSOR_LEFT;
	}

	if (Input::IsTriggerButton(Input::BUTTON_B))
	{
		m_UITrigger = INPUT_SELECT;
	}
	if (Input::IsTriggerButton(Input::BUTTON_A))
	{
		m_UITrigger = INPUT_CANCEL;
	}
}
