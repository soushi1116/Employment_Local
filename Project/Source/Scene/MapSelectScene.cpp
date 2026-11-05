#include "DxLib.h"
#include "MapSelectScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Mission/MissionManager.h"
#include "../MyMath/MyMath.h"
#include "../Sound/SoundManager.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"
#include "../Managers/MapManager/MapManager.h"
#include "../Managers/BattleManager/BattleManager.h"

const VECTOR MAP_SELECT_TEXT_POS = MyMath::Vec2D(800.0f, 200.0f);
const VECTOR MAP_TEST_POS = MyMath::Vec2D(300.0f, 500.0f);
const VECTOR MAP_FACTORY_POS = MyMath::Vec2D(800.0f, 500.0f);
const VECTOR MAP_FOREST_POS = MyMath::Vec2D(1300.0f, 500.0f);

MapSelectScene::MapSelectScene() : SceneBase()
{

}

MapSelectScene::~MapSelectScene()
{

}

void MapSelectScene::Init()
{
	
}

void MapSelectScene::Load()
{
	
}

void MapSelectScene::Start()
{
	SceneBase::Start();

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlayBGM(BGM_SELECT);

	RendererManager* rendererManager = RendererManager::GetInstance();

	auto mapSelectGroupObj = rendererManager->CreateButtonGroup(GROUP_NAME_BOSS_SELECT);

	std::shared_ptr<UIButtonGroup> mapSelectGroup = mapSelectGroupObj->GetComponent<UIButtonGroup>();

	auto bgObj = rendererManager->CreateBackGround("Data/BackGround/MissionSelectScene.png");
	auto mapSelectTextObj = rendererManager->CreateUIImage("Data/UI/BossSelectScene/BossSelect.png", MAP_SELECT_TEXT_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f);
	auto buttonTestMapObj = rendererManager->CreateUIButton("Data/UI/MapSelectScene/TestMap.png", MAP_TEST_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(1, 1), mapSelectGroup);
	auto buttonFactoryMapObj = rendererManager->CreateUIButton("Data/UI/MapSelectScene/Factory.png", MAP_FACTORY_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(2, 1), mapSelectGroup);
	auto buttonForestMapObj = rendererManager->CreateUIButton("Data/UI/MapSelectScene/Forest.png", MAP_FOREST_POS, VGet(1.0f, 1.0f, 1.0f), 0.0f, MyMath::Vec2DInt(3, 1), mapSelectGroup);

	mapSelectGroup->SetTotalIndex(MyMath::Vec2DInt(3, 1));

	Instantiate(mapSelectGroupObj);
	Instantiate(bgObj);
	Instantiate(mapSelectTextObj);
	Instantiate(buttonTestMapObj);
	Instantiate(buttonFactoryMapObj);
	Instantiate(buttonForestMapObj);

	mapSelectGroup->SetActive(true);
}

void MapSelectScene::Step()
{
	RendererManager::GetInstance()->CheckCursor(m_UIInputCmp);

	if (m_UIInputCmp->IsTriggerUI(INPUT_SELECT))
	{
		if (!m_SceneChangeStart)
		{
			Event::SetStartCount();

			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->PlaySE(SE_CURSOR_SELECT);
		}

		m_SceneChangeStart = true;
	}
	else if (m_UIInputCmp->IsTriggerUI(INPUT_CANCEL))
	{
		if (!m_SceneChangeStart)
		{
			Event::SetStartCount();

			Sound* sound = SoundManager::GetInstance()->GetSound();
			sound->PlaySE(SE_CANCEL);

			m_SceneBack = true;
		}

		m_SceneChangeStart = true;
	}
}

void MapSelectScene::Update()
{
	SceneBase::Update();

	RendererManager* rendererManager = RendererManager::GetInstance();
	MyMath::VECTOR_INT currentIndex = rendererManager->GetCurrentIndex();

	if (m_SceneChangeEnd)
	{
		if (m_SceneBack)
		{
			Sound* sound = SoundManager::GetInstance()->GetSound();

			SceneManager::GetInstance()->ChangeScene(CHARACTER_SELECT);
		}
		else
		{
			BattleManager* battleManager = BattleManager::GetInstance();

			if (currentIndex.y == 1)
			{
				if (currentIndex.x == 1)
				{
					battleManager->SetMapType(MAP_TEST);
				}
				else if (currentIndex.x == 2)
				{
					battleManager->SetMapType(MAP_FACTORY);
				}
				else if (currentIndex.x == 3)
				{
					battleManager->SetMapType(MAP_FOREST);
				}
			}

			SoundManager::GetInstance()->GetSound()->StopBGM(BGM_SELECT);
			SceneManager::GetInstance()->ChangeScene(BATTLE);
		}
	}

}

void MapSelectScene::Draw()
{
	SceneBase::Draw();
}

void MapSelectScene::Fin()
{
	SceneBase::Fin();
}