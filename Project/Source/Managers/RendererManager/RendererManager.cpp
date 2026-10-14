#include "RendererManager.h"
#include "../../Component/Component.h"
#include "../../Component/GameObject.h"
#include "../../Component/AllComponents.h"

RendererManager* RendererManager::m_Instance = nullptr;

RendererManager::RendererManager()
{
	
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
	
}

void RendererManager::Step()
{

}

void RendererManager::Update()
{
	
}

void RendererManager::Draw()
{

}

void RendererManager::Fin()
{

}


std::shared_ptr<GameObject> RendererManager::CreateBackGround(const char* filePath)
{
	auto bgObj = std::make_shared<GameObject>();

	auto backGroundRenderer = bgObj->AddComponent<BackGroundRenderer>(filePath);

	return bgObj;
}

std::shared_ptr<GameObject> RendererManager::CreateUIImage(const char* filePath, VECTOR pos, float exRate, float angle)
{
	auto imageObj = std::make_shared<GameObject>();

	auto renderer = imageObj->AddComponent<SpriteRenderer>(filePath);

	renderer->SetPos(pos);
	renderer->SetExRate(exRate);
	renderer->SetAngle(angle);

	return imageObj;
}

std::shared_ptr<GameObject> RendererManager::CreateUIButton(const char* filePath, VECTOR pos, float exRate, float angle, MyMath::VECTOR_INT index, std::shared_ptr<UIButtonGroup> parent)
{
	auto buttonObj = std::make_shared<GameObject>();

	auto renderer = buttonObj->AddComponent<SpriteRenderer>(filePath);

	renderer->SetPos(pos);
	renderer->SetExRate(exRate);
	renderer->SetAngle(angle);

	auto uiButton = buttonObj->AddComponent<UIButton>();
	uiButton->SetIndex(index);
	uiButton->SetParent(parent);

	return buttonObj;
}

std::shared_ptr<GameObject> RendererManager::CreateUIText()
{
	auto uiText = std::make_shared<GameObject>();

	return uiText;
}

std::shared_ptr<GameObject> RendererManager::CreateButtonGroup(ButtonGroupName name)
{
	auto groupObj = std::make_shared<GameObject>();

	auto buttonGroup = groupObj->AddComponent<UIButtonGroup>();
	buttonGroup->SetGroupName(name);

	m_UIButtonGroups.push_back(buttonGroup);

	return groupObj;
}

MyMath::VECTOR_INT RendererManager::GetCurrentIndex()
{
	for (auto& group : m_UIButtonGroups)
	{
		if (group->IsActive())
		{
			return group->GetCurrentIndex();
		}
	}
	return MyMath::Vec2DInt(0, 0);
}

void RendererManager::CheckCursor(std::shared_ptr<UIInput> input)
{
	for (auto& group : m_UIButtonGroups)
	{
		if (group->IsActive())
		{
			group->CheckCursor(input);
		}
	}
}

ButtonGroupName RendererManager::GetActiveButtonGroup()
{
	for (auto& group : m_UIButtonGroups)
	{
		if (group->IsActive())
		{
			return group->GetGroupName();
		}
	}
	return GROUP_NAME_NONE;
}