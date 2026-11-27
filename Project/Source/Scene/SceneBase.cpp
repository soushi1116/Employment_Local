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
#include "../MyColor/MyColor.h"
#include "../ShadowMap/ShadowMap.h"

constexpr int CHANGE_SCENE_INTERVAL = 2;

SceneBase* SceneBase::s_Instance = nullptr;

SceneBase::SceneBase()
	:m_SceneChangeStart(false)
	, m_SceneChangeEnd(false)
	, m_SceneBack(false)
{
	s_Instance = this;
}

SceneBase::~SceneBase()
{

}

void SceneBase::Start()
{
	m_UIInputObj = GetOneGameObjectByTag(TAG_UI_INPUT);

	if (m_UIInputObj == nullptr)
	{
		InputManager* inputManager = InputManager::GetInstance();
		m_UIInputObj = inputManager->CreateUIInput();

		m_GameObjects.push_back(m_UIInputObj);
	}

	m_UIInputCmp = m_UIInputObj->GetComponent<UIInput>();

	for (auto& go : m_GameObjects)
	{
		go->Start();
	}

	RendererManager::GetInstance()->Start();
}

void SceneBase::Update()
{
	if (!m_NewGameObjects.empty())
	{
		std::vector<std::shared_ptr<GameObject>> newObject = std::move(m_NewGameObjects);
		m_NewGameObjects.clear();

		for (auto& newObj : newObject)
		{
			m_GameObjects.push_back(newObj);
			newObj->Start();
		}

		SortRayerIndex();
	}

	for (auto& go : m_GameObjects)
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
	auto shadowMap = ShadowMap::GetInstance();

	shadowMap->StartDrawShadowMap();

	for (auto& go : m_GameObjects)
	{
		if (go->GetComponent<ModelRenderer>())
		{
			go->Draw();
		}
	}

	shadowMap->EndDrawShadowMap();

	shadowMap->StartAppearsShadowMap();

	for (auto& go : m_GameObjects)
	{
		go->Draw();
	}

	shadowMap->EndAppearsShadowMap();
}

void SceneBase::Fin()
{
	for (auto& obj : m_GameObjects)
	{
		obj->SetActive(false);
	}

	DeleteGameObject();

	m_GameObjects.clear();
}

void SceneBase::SortRayerIndex()
{
	auto boundary = std::stable_partition(m_GameObjects.begin(), m_GameObjects.end(),
		[](const std::shared_ptr<GameObject>& obj) {
			auto rendererBase = obj->GetComponent<RendererBase>();
			return rendererBase;
		});

	std::stable_sort(m_GameObjects.begin(), boundary,
		[](const std::shared_ptr<GameObject>& a, const std::shared_ptr<GameObject>& b) {
			int indexA = a->GetComponent<RendererBase>()->GetRayerIndex();
			int indexB = b->GetComponent<RendererBase>()->GetRayerIndex();
			return indexA < indexB;
		});
}

std::shared_ptr<GameObject> SceneBase::GetOneGameObjectByTag(Tag tag)
{
	for (auto& go : m_GameObjects)
	{
		if (go->CompareTag(tag))
		{
			return go;
		}
	}

	return nullptr;
}

std::vector<std::shared_ptr<GameObject>> SceneBase::GetGameObjectsByTag(Tag tag)
{
	std::vector<std::shared_ptr<GameObject>> objs;

	for (const auto& obj : m_GameObjects)
	{
		if (obj->CompareTag(tag))
		{
			objs.push_back(obj);
		}
	}

	return objs;
}

void SceneBase::DeleteGameObject()
{
	m_GameObjects.erase(
		std::remove_if(m_GameObjects.begin(), m_GameObjects.end(),
			[] (const auto& go)
	{
		return go == nullptr || !go->IsActive();
	}),
		m_GameObjects.end()
	);
}