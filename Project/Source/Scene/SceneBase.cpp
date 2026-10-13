#include "SceneBase.h"
#include "../Input/Input.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"
#include "../Sound/SoundManager.h"
#include "../Managers/InputManager/InputManager.h"
#include "../Component/AllComponents.h"
#include "../Managers/RendererManager/RendererManager.h"

const int CHANGE_SCENE_INTERVAL = 2;

SceneBase* SceneBase::s_Instance = nullptr;

SceneBase::SceneBase()
{
	m_BGHandle = 0;
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

void SceneBase::Draw()
{
	for (auto go : m_GameObjects)
	{
		go->Draw();
	}
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