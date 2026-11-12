#include "DxLib.h"
#include "DebugScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Managers/CharacterManager/CharacterManager.h"
#include "../Managers/CameraManager/CameraManager.h"
#include "../Managers/MapManager/MapManager.h"
#include "../ShadowMap/ShadowMap.h"
#include "../Managers/CollisionManager/CollisionManager.h"
#include "../MyMath/MyMath.h"
#include "../Managers/BulletManager/BulletManager.h"
#include "../Managers/BattleManager/BattleManager.h"
#include "../Managers/EffectManager/EffectManager.h"
#include "../SkyDome/SkyDome.h"
#include "../Managers/MissionManager/MissionManager.h"
#include "../Managers/ItemManager/ItemManager.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"

DebugScene::DebugScene() : SceneBase()
{
	m_BattleFinishCountDebug = 0;
	m_BattleFinishedDebug = false;
	m_SkyDome = nullptr;
}

DebugScene::~DebugScene()
{

}

void DebugScene::Init()
{
	m_GameObjects.clear();

	CollisionManager::CreateInstance();

	MissionManager::CreateInstance();

	BattleManager::CreateInstance();
	BattleManager* battleManager = BattleManager::GetInstance();
	battleManager->Init();

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	/*BulletManager::CreateInstance();
	BulletManager* bulletManager = BulletManager::GetInstance();
	bulletManager->Init();*/

	BulletManager::CreateInstance();

	//CharacterManager* characterManager = CharacterManager::GetInstance();
	//characterManager->Init();

	MapManager::CreateInstance();
	MapManager* mapManager = MapManager::GetInstance();
	
	auto map = mapManager->CreateMap(MAP_FACTORY);

	m_SkyDome = new SkyDome;

	ShadowMap::CreateInstance();
	ShadowMap::GetInstance()->Init();

	EffectManager::GetInstance()->Init();

	ItemManager::CreateInstance();
	//ItemManager* itemManager = ItemManager::GetInstance();
	//itemManager->Init();
}

void DebugScene::Load()
{
	//MissionManager::GetInstance()->Load();
	//CharacterManager::GetInstance()->Load();
	//ItemManager::GetInstance()->Load();
	//BulletManager::GetInstance()->Load();
	EffectManager::GetInstance()->Load();
	//BattleManager::GetInstance()->Load();

	m_SkyDome->Load();
}

void DebugScene::Start()
{
	SceneBase::Start();

	//MissionManager::GetInstance()->Start();

	CharacterManager* characterManager = CharacterManager::GetInstance();

	characterManager->CreateCharacter(true, true, CharacterType::ROBOT);
	characterManager->CreateCharacter(false, true, CharacterType::KNIGHT);
	//characterManager->CreateCharacter(false, true, CharacterType::FAIRY);
	//characterManager->CreateCharacter(false, true, CharacterType::NINJA);
	//characterManager->SetBossNum(1);

	BattleManager::GetInstance()->BattleStart();

	//characterManager->Start();

	//auto characterList = characterManager->GetCharacterList();

	/*for (auto character : characterList)
	{
		character->ChangeInBattleScene(true);
	}*/


	//BulletManager::GetInstance()->Start();

	//ItemManager::GetInstance()->Start();
	//BulletManager::GetInstance()->Start();

	//EffekseerManager::GetInstance()->Start();

	//CharacterBase* player = characterManager->SearchPlayer();
	//CameraBase* camera = cameraManager->GetCamera(CAMERA);
	//camera->SetTargetCharacter(player);

	//BattleManager::GetInstance()->Start();

	ChangeLightTypePoint(MyMath::VecZero(), 5000.0f, 0.0f, 0.002f, 0.0f);

	SetLightPosition(MyMath::VecY(300.0f));
	SetLightDirection(MyMath::VecX(10.0f));
}

void DebugScene::Step()
{
	//MissionManager::GetInstance()->Step();
	//BulletManager::GetInstance()->Step();
	EffectManager::GetInstance()->Step();
	//CharacterManager::GetInstance()->Step();
	ItemManager::GetInstance()->Step();
	BattleManager::GetInstance()->Step();

	SceneManager* sceneManager = SceneManager::GetInstance();

	if (Input::IsTriggerButton(Input::BUTTON_X))
	{
		sceneManager->ChangeScene(HOME);
	}

	BattleManager* battleManager = BattleManager::GetInstance();

	if (Input::IsTriggerKey(Input::KEY_LEFT))
	{
		battleManager->BossWin();
	}
	if (Input::IsTriggerKey(Input::KEY_RIGHT))
	{
		battleManager->ChallengerWin();
	}

	if (Input::IsTriggerKey(Input::KEY_UP))
	{
		//MissionManager::GetInstance()->CreateMission();
	}

	bool isBossWin = battleManager->IsBossWin();
	bool isChallengerWin = battleManager->IsChallengerWin();

	if (isBossWin || isChallengerWin)
	{
		if (!m_SceneChangeStart)
		{
			Event::SetStartCount();
		}

		m_SceneChangeStart = true;
	}

	m_SkyDome->Step();
}

void DebugScene::Update()
{
	SceneBase::Update();

	CollisionManager::GetInstance()->CheckCollision();

	for (auto& go : m_GameObjects)
	{
		go->ApplyPushBack();
	}

	//MissionManager::GetInstance()->Update();
	//BulletManager::GetInstance()->Update();
	//CameraManager::GetInstance()->Update();
	//CharacterManager::GetInstance()->Update();
	ItemManager::GetInstance()->Update();
	EffectManager::GetInstance()->Update();

	MissionManager::GetInstance()->Update();

	FPSSystem* fps = FPSManager::GetInstance()->GetFPS();

	if (m_SceneChangeEnd)
	{
		BattleManager* battleManager = BattleManager::GetInstance();

		bool isBossWin = battleManager->IsBossWin();
		bool isChallengerWin = battleManager->IsChallengerWin();

		const auto& characters = CharacterManager::GetInstance()->GetCharacters();
		for (auto& character : characters)
		{
			const auto& characterShared = character.lock();

			if (!characterShared) continue;

			const auto& characterParam = characterShared->GetComponent<CharacterParameter>();

			CharacterManager::GetInstance()->AddParametersForResult(characterParam);
		}

		SceneManager::GetInstance()->ChangeScene(RESULT);
	}

	//if (!m_BattleFinishedDebug)
	//{
	//	if (BattleManager::GetInstance()->IsBossWin())
	//	{
	//		//uiManager->CreateUIImage(UI_BOSS_WIN, MyMath::Vec2D(800.0f, 500.0f));
	//		m_BattleFinishedDebug = true;
	//		m_BattleFinishCountDebug = fps->GetTotalTime();
	//		//CharacterManager::GetInstance()->SetWinnerBoss(true);
	//	}

	//	if (BattleManager::GetInstance()->IsChallengerWin())
	//	{
	//		//uiManager->CreateUIImage(UI_CHALLENGER_WIN, MyMath::Vec2D(800.0f, 500.0f));
	//		m_BattleFinishedDebug = true;
	//		m_BattleFinishCountDebug = fps->GetTotalTime();
	//		//CharacterManager::GetInstance()->SetWinnerBoss(false);
	//	}
	//}
	//else
	//{
	//	//uiManager->CreateUIImage(UI_BATTLE_FINISH, MyMath::Vec2D(800.0f, 200.0f));

	//	if (fps->GetTotalTime() - m_BattleFinishCountDebug > 3)
	//	{
	//		SceneManager::GetInstance()->ChangeScene(RESULT);
	//	}
	//}

	m_SkyDome->Update();

	BulletManager::GetInstance()->Update();
}

void DebugScene::Draw()
{
	SceneBase::Draw();

	//m_SkyDome->Draw();

	//CharacterManager* characterManager = CharacterManager::GetInstance();
	ShadowMap* shadowMap = ShadowMap::GetInstance();

	shadowMap->StartDrawShadowMap();
	//characterManager->DrawModel();
	//ItemManager::GetInstance()->Draw();
	//BulletManager::GetInstance()->Draw();
	shadowMap->EndDrawShadowMap();

	shadowMap->StartAppearsShadowMap();
	shadowMap->EndAppearsShadowMap();

	//characterManager->DrawModel();
	//ItemManager::GetInstance()->Draw();
	//BulletManager::GetInstance()->Draw();

	//CollisionManager::GetInstance()->Draw();


	EffectManager::GetInstance()->Draw();

	//MissionManager::GetInstance()->Draw();

	//characterManager->DrawUI();

	//BattleManager::GetInstance()->Draw();
}

void DebugScene::Fin()
{
	SceneBase::Fin();

	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	//MissionManager::DeleteInstance();
	//BulletManager::DeleteInstance();
	MapManager::DeleteInstance();
	CollisionManager::DeleteInstance();
	ItemManager::DeleteInstance();
	//CharacterManager::GetInstance()->ClearRooter();

	delete m_SkyDome;
}