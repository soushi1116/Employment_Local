#include "SceneBase.h"
#include "../Input/Input.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"
#include "../Sound/SoundManager.h"
#include "../Managers/InputManager/InputManager.h"
#include "../Component/AllComponents.h"
#include "../Managers/RendererManager/RendererManager.h"
#include "../Component/GameObject.h"
#include <algorithm>

const int CHANGE_SCENE_INTERVAL = 2;

SceneBase* SceneBase::s_Instance = nullptr;

SceneBase::SceneBase()
{
	m_SceneChangeStart = false;
	m_SceneChangeEnd = false;
	m_SceneBack = false;

	s_Instance = this;
}

SceneBase::~SceneBase()
{

}

void SceneBase::Start()
{
	m_UIInputObj = SearchGameObjectTag(TAG_UI_INPUT);

	if (m_UIInputObj == nullptr)
	{
		InputManager* inputManager = InputManager::GetInstance();
		m_UIInputObj = inputManager->CreateUIInput();

		m_GameObjects.push_back(m_UIInputObj);
	}

	m_UIInputCmp = m_UIInputObj->GetComponent<UIInput>();

	for (auto go : m_GameObjects)
	{
		go->Start();
	}

	RendererManager::GetInstance()->Start();
}

void SceneBase::Update()
{
	if (!m_NewGameObjects.empty())
	{
		for (auto& newObj : m_NewGameObjects)
		{
			m_GameObjects.push_back(newObj);
			newObj->Start();
		}
		m_NewGameObjects.clear();
	}

	for (auto go : m_GameObjects)
	{
		go->Update();
	}

	

	if (Event::ChangeScene(CHANGE_SCENE_INTERVAL))
	{
		m_SceneChangeEnd = true;

		Event::ResetCount();
	}
	RendererManager::GetInstance()->Update();

}

void SceneBase::RateUpdate()
{
	DeleteGameObject();
}

void SceneBase::Draw()
{
	for (auto go : m_GameObjects)
	{
		go->Draw();
	}
}

void SceneBase::Fin()
{
	m_GameObjects.clear();
}

std::shared_ptr<GameObject> SceneBase::SearchGameObjectTag(Tag tag)
{
	for (auto go : m_GameObjects)
	{
		if (go->CompareTag(tag))
		{
			return go;
		}
	}

	return nullptr;
}

void SceneBase::DeleteGameObject()
{
	for (auto go : m_GameObjects)
	{
		if (go == nullptr) continue;

		if (!go->IsActive())
		{
			std::remove_if(m_GameObjects.begin(), m_GameObjects.end(),
				[](const auto& go)
				{
					return go == nullptr || !go->IsActive();
				}),
				m_GameObjects.end();
		}
	}
}