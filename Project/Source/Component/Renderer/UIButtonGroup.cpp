#include "UIButtonGroup.h"
#include "../GameObject.h"
#include "../../Sound/SoundManager.h"
#include "../Timer/Timer.h"

const float CURSOR_MOVE_INTERVAL = 0.2f;

UIButtonGroup::UIButtonGroup(GameObject* owner) : Component(owner)
{
	m_Active = false;
	m_InactiveInvisible = false;
	m_GroupName = GROUP_NAME_NONE;

	m_TotalIndex = MyMath::Vec2DInt(0, 0);

	m_CurrentIndex = MyMath::Vec2DInt(0, 0);
}

UIButtonGroup::~UIButtonGroup()
{

}

void UIButtonGroup::Start()
{
	m_CurrentIndex = MyMath::Vec2DInt(1, 1);
}

void UIButtonGroup::Update()
{
	if (!m_Active)
	{
		for (auto& button : m_UIButtons)
		{
			button->SetIsSelected(false);
		}
		return;
	}

	for (auto& button : m_UIButtons)
	{
		if (button->GetIndex().x == m_CurrentIndex.x && button->GetIndex().y == m_CurrentIndex.y)
		{
			button->SetIsSelected(true);
		}
		else
		{
			button->SetIsSelected(false);
		}
	}
}

void UIButtonGroup::CheckCursor(std::shared_ptr<UIInput> input)
{
	if (!m_Active) return;

	auto timerPtr = m_CursorTimer.lock();

	if (!timerPtr) return;

	Sound* sound = SoundManager::GetInstance()->GetSound();

	if (timerPtr->IsCountEnd())
	{
		if (input->IsInputUI(CURSOR_UP))
		{
			if (m_CurrentIndex.y > 1)
			{
				sound->PlaySE(SE_CURSOR_MOVE);
				m_CurrentIndex.y--;
				timerPtr->ResetCount();
				timerPtr->CountStart(CURSOR_MOVE_INTERVAL);
			}
		}
		if (input->IsInputUI(CURSOR_RIGHT))
		{
			if (m_CurrentIndex.x < m_TotalIndex.x)
			{
				sound->PlaySE(SE_CURSOR_MOVE);
				m_CurrentIndex.x++;
				timerPtr->ResetCount();
				timerPtr->CountStart(CURSOR_MOVE_INTERVAL);
			}
		}
		if (input->IsInputUI(CURSOR_DOWN))
		{
			if (m_CurrentIndex.y < m_TotalIndex.y)
			{
				sound->PlaySE(SE_CURSOR_MOVE);
				m_CurrentIndex.y++;
				timerPtr->ResetCount();
				timerPtr->CountStart(CURSOR_MOVE_INTERVAL);
			}
		}
		if (input->IsInputUI(CURSOR_LEFT))
		{
			if (m_CurrentIndex.x > 1)
			{
				sound->PlaySE(SE_CURSOR_MOVE);
				m_CurrentIndex.x--;
				timerPtr->ResetCount();
				timerPtr->CountStart(CURSOR_MOVE_INTERVAL);
			}
		}
	}
}
