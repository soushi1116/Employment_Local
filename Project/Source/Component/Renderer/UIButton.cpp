#include "../Component.h"
#include "UIButton.h"
#include "DxLib.h"
#include "../GameObject.h"
#include "SpriteRenderer.h"

UIButton::UIButton(GameObject* owner) : Component(owner)
{
	m_CompName = "UIButton";

	m_Index.x = 0;
	m_Index.y = 0;

	m_IsSelected = false;

}

UIButton::~UIButton()
{
	
}

void UIButton::Start()
{
	if (auto rendererPtr = m_SpriteRenderer.lock())
	{
		rendererPtr = m_Owner->GetComponent<SpriteRenderer>();
	}
}

void UIButton::Update()
{
	auto rendererPtr = m_SpriteRenderer.lock();
	auto groupPtr = m_ParentGroup.lock();

	if (!rendererPtr)
	{
		m_SpriteRenderer = m_Owner->GetComponent<SpriteRenderer>();
	}

	if (!rendererPtr) return;

	if (!groupPtr) return;

	if (groupPtr->IsInactiveInvisible() && !groupPtr->IsActive())
	{
		rendererPtr->SetActive(false);
	}
	else
	{
		rendererPtr->SetActive(true);
	}

	if (m_IsSelected)
	{
		rendererPtr->SetBright(1.0f);
	}
	else
	{
		rendererPtr->SetBright(0.5f);
	}
}

void UIButton::SetParent(std::weak_ptr<UIButtonGroup> parent)
{
	auto parentPtr = parent.lock();
	m_ParentGroup = parentPtr;
	parentPtr->AddUIButton(this);
}