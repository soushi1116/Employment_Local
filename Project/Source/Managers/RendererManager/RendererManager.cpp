#include "RendererManager.h"
#include "../../Component/Component.h"
#include "../../Component/GameObject.h"
#include "../../Component/AllComponents.h"

RendererManager* RendererManager::m_Instance = nullptr;

RendererManager::RendererManager()
{
	m_TotalIndex = MyMath::Vec2DInt(0, 0);

	m_CurrentIndex = MyMath::Vec2DInt(0, 0);
}

RendererManager::~RendererManager()
{

}

void RendererManager::Init()
{

}

void RendererManager::Load()
{

}

void RendererManager::Start()
{
	m_CurrentIndex = MyMath::Vec2DInt(1, 1);
}

void RendererManager::Step()
{

}

void RendererManager::Update()
{
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

void RendererManager::Draw()
{

}

void RendererManager::Fin()
{

}

void RendererManager::CheckCursor(std::shared_ptr<UIInput> input)
{
	if (input->IsInputUI(CURSOR_UP))
	{
		if (m_CurrentIndex.y > 1)
		{
			m_CurrentIndex.y--;
		}
	}
	if (input->IsInputUI(CURSOR_RIGHT))
	{
		if (m_CurrentIndex.x < m_TotalIndex.x)
		{
			m_CurrentIndex.x++;
		}
	}
	if (input->IsInputUI(CURSOR_DOWN))
	{
		if (m_CurrentIndex.y < m_TotalIndex.y)
		{
			m_CurrentIndex.y++;
		}
	}
	if (input->IsInputUI(CURSOR_LEFT))
	{
		if (m_CurrentIndex.x > 1)
		{
			m_CurrentIndex.x--;
		}
	}
}

std::shared_ptr<GameObject> RendererManager::CreateBackGround(const char* filePath)
{
	auto backGround = std::make_shared<GameObject>();

	auto backGroundRenderer = backGround->AddComponent<BackGroundRenderer>(filePath);

	return backGround;
}

std::shared_ptr<GameObject> RendererManager::CreateUIImage(const char* filePath, VECTOR pos, float exRate, float angle)
{
	auto newImage = std::make_shared<GameObject>();

	auto renderer = newImage->AddComponent<SpriteRenderer>(filePath);

	renderer->SetPos(pos);
	renderer->SetExRate(exRate);
	renderer->SetAngle(angle);

	return newImage;
}

std::shared_ptr<GameObject> RendererManager::CreateUIButton(const char* filePath, VECTOR pos, float exRate, float angle, MyMath::VECTOR_INT index)
{
	auto newButton = std::make_shared<GameObject>();

	auto renderer = newButton->AddComponent<SpriteRenderer>(filePath);

	renderer->SetPos(pos);
	renderer->SetExRate(exRate);
	renderer->SetAngle(angle);

	auto uiButton = newButton->AddComponent<UIButton>();
	uiButton->SetIndex(index);

	m_UIButtons.push_back(uiButton);

	return newButton;
}

std::shared_ptr<GameObject> RendererManager::CreateUIText()
{
	auto uiText = std::make_shared<GameObject>();

	return uiText;
}