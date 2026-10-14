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
	m_SpriteRenderer = m_Owner->GetComponent<SpriteRenderer>();
}

void UIButton::Update()
{
	if (m_SpriteRenderer == nullptr)
	{
		m_SpriteRenderer = m_Owner->GetComponent<SpriteRenderer>();
	}

	if (m_ParentGroup->IsInactiveInvisible() && !m_ParentGroup->IsActive())
	{
		m_SpriteRenderer->SetActive(false);
	}
	else
	{
		m_SpriteRenderer->SetActive(true);
	}

	if (m_IsSelected)
	{
		m_SpriteRenderer->SetAlpha(1.0f);
	}
	else
	{
		m_SpriteRenderer->SetAlpha(0.5f);
	}
}

void UIButton::SetParent(std::shared_ptr<UIButtonGroup> parent)
{
	m_ParentGroup = parent;
	parent->AddUIButton(std::shared_ptr<UIButton>(this));
}