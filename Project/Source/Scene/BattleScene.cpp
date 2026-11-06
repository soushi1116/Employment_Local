#include "DxLib.h"
#include "BattleScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Managers/CharacterManager/CharacterManager.h"
#include "../Camera/CameraManager.h"
#include "../Managers/MapManager/MapManager.h"
#include "../ShadowMap/ShadowMap.h"
#include "../Collision/CollisionManager.h"
#include "../Item/ItemManager.h"
#include "../Mission/MissionManager.h"
#include "../Managers/BattleManager/BattleManager.h"
#include "../Managers/BulletManager/BulletManager.h"
#include "../Managers/EffectManager/EffectManager.h"
#include "../MyMath/MyMath.h"
#include "../FPS/FPSManager.h"
#include "../Sound/SoundManager.h"
#include "../SkyDome/SkyDome.h"

const VECTOR UI_SKILL_POS = VGet(175.0f, 775.0f, 0.0f);
const VECTOR UI_SUPER_ATTACK_POS = VGet(475.0f, 775.0f, 0.0f);
const float UI_SKILL_AND_SUPER_ATTACK_RADIUS = 75.0f;

BattleScene::BattleScene() : SceneBase()
{
	m_BattleFinishCount = 0;
	m_BattleFinished = false;

	m_SkyDome = nullptr;
}

BattleScene::~BattleScene()
{

}

void BattleScene::Init()
{
	MapManager::CreateInstance();

	BattleManager* battleManager = BattleManager::GetInstance();
	battleManager->Init();

	/*MissionManager::CreateInstance();
	MissionManager* missionManager = MissionManager::GetInstance();
	missionManager->Init();*/

	CollisionManager::CreateInstance();

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	ItemManager::CreateInstance();
	ItemManager* itemManager = ItemManager::GetInstance();
	itemManager->Init();

	BulletManager::CreateInstance();
	BulletManager* bulletManager = BulletManager::GetInstance();
	bulletManager->Init();

	m_SkyDome = new SkyDome;

	ShadowMap::CreateInstance();
	ShadowMap::GetInstance()->Init();

	//EffekseerManager::GetInstance()->Init();
}

void BattleScene::Load()
{
	/*MissionManager::GetInstance()->Load();
	CharacterManager::GetInstance()->Load();
	ItemManager::GetInstance()->Load();
	BulletManager::GetInstance()->Load();
	CameraManager::GetInstance()->Load();
	EffekseerManager::GetInstance()->Load();
	BattleManager::GetInstance()->Load();*/

	m_SkyDome->Load();
}

void BattleScene::Start()
{
	SceneBase::Start();

	//MissionManager::GetInstance()->Start();

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlayBGM(BGM_BATTLE);

	MapManager* mapManager = MapManager::GetInstance();
	BattleManager* battleManager = BattleManager::GetInstance();

	mapManager->CreateMap(battleManager->GetMapType());

	CharacterManager* characterManager = CharacterManager::GetInstance();
	
	for (int i = 0; i < CHARACTER_MAX_NUM; i++)
	{
		CharacterType characterType = characterManager->GetCharacterType(i);

		if (i == characterManager->GetBossNum())
		{
			if (i == 0)
			{
				characterManager->CreateCharacter(true, true, characterType);
			}
			else
			{
				characterManager->CreateCharacter(false, true, characterType);
			}
		}
		else
		{
			if (i == 0)
			{
				characterManager->CreateCharacter(true, true, characterType);
			}
			else
			{
				characterManager->CreateCharacter(false, true, characterType);
			}
		}
	}

	BattleManager::GetInstance()->BattleStart();
	
	//characterManager->Start();

	/*auto characterList = characterManager->GetCharacterList();
	
	for (auto character : characterList)
	{
		character->ChangeInBattleScene(true);
	}*/

	//ItemManager::GetInstance()->Start();
	//BulletManager::GetInstance()->Start();

	/*CameraManager* cameraManager = CameraManager::GetInstance();
	cameraManager->SetActiveCamera(PLAYER_CAMERA);
	cameraManager->Start();*/

	//EffekseerManager::GetInstance()->Start();

	//CharacterBase* player = characterManager->SearchPlayer();
	//CameraBase* camera = cameraManager->GetCamera(PLAYER_CAMERA);
	//camera->SetTargetCharacter(player);

	BattleManager::GetInstance()->Start();

	DxLib::ChangeLightTypePoint(MyMath::VecZero(), 500.0f, 0.0f, 0.002f, 0.0f);

	DxLib::SetLightPosition(MyMath::VecY(300.0f));
	DxLib::SetLightDirection(MyMath::VecX(10.0f));
}

void BattleScene::Step()
{
	//MissionManager::GetInstance()->Step();
	BattleManager::GetInstance()->Step();
	ItemManager::GetInstance()->Step();
	BulletManager::GetInstance()->Step();
	CameraManager::GetInstance()->Step();
	//EffekseerManager::GetInstance()->Step();
	CollisionManager::GetInstance()->CheckCollision();

	SceneManager* sceneManager = SceneManager::GetInstance();

	if (Input::IsTriggerButton(Input::BUTTON_X))
	{
		sceneManager->ChangeScene(HOME);
	}

	m_SkyDome->Step();
}

void BattleScene::Update()
{
	SceneBase::Update();

	CollisionManager::GetInstance()->CheckCollision();

	for (auto& go : m_GameObjects)
	{
		std::shared_ptr< Physics3D> physics = go->GetComponent<Physics3D>();

		if (physics != nullptr)
		{
			go->ApplyPushBack();
		}
	}

	//MissionManager::GetInstance()->Update();
	ItemManager::GetInstance()->Update();
	BulletManager::GetInstance()->Update();
	CameraManager::GetInstance()->Update();
	EffectManager::GetInstance()->Update();

	SceneManager* sceneManager = SceneManager::GetInstance();
	FPSSystem* fps = FPSManager::GetInstance()->GetFPS();

	//if (!m_BattleFinished)
	//{
	//	if (BattleManager::GetInstance()->IsBossWin())
	//	{
	//		//uiManager->CreateUIImage(UI_BOSS_WIN, MyMath::Vec2D(800.0f, 500.0f));
	//		m_BattleFinished = true;
	//		m_BattleFinishCount = fps->GetDeltaTime();
	//		characterManager->SetWinnerBoss(true);
	//	}

	//	if (BattleManager::GetInstance()->IsChallengerWin())
	//	{
	//		//uiManager->CreateUIImage(UI_CHALLENGER_WIN, MyMath::Vec2D(800.0f, 500.0f));
	//		m_BattleFinished = true;
	//		m_BattleFinishCount = fps->GetDeltaTime();
	//		characterManager->SetWinnerBoss(false);
	//	}
	//}
	//else
	//{
	//	if (fps->GetTotalTime() - m_BattleFinishCount > 3)
	//	{
	//		sceneManager->ChangeScene(RESULT);
	//	}
	//}

	m_SkyDome->Update();
}

void BattleScene::Draw()
{
	SceneBase::Draw();

	if (m_BattleFinished)
	{
		SetDrawBright(128, 128, 128);
	}

	m_SkyDome->Draw();

	//CharacterManager* characterManager = CharacterManager::GetInstance();
	ShadowMap* shadowMap = ShadowMap::GetInstance();

	/*shadowMap->StartDrawShadowMap();
	characterManager->DrawModel();
	ItemManager::GetInstance()->Draw();
	BulletManager::GetInstance()->Draw();
	shadowMap->EndDrawShadowMap();

	shadowMap->StartAppearsShadowMap();
	shadowMap->EndAppearsShadowMap();

	characterManager->DrawModel();
	ItemManager::GetInstance()->Draw();
	BulletManager::GetInstance()->Draw();*/
	CameraManager::GetInstance()->Draw();

	//CollisionManager::GetInstance()->Draw();

	//EffekseerManager::GetInstance()->Draw();

	//BattleManager::GetInstance()->Draw();

	//MissionManager::GetInstance()->Draw();

	//characterManager->DrawUI();

	SetDrawBright(255, 255, 255);

}

void BattleScene::Fin()
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	//MissionManager::DeleteInstance();
	MapManager::DeleteInstance();
	CollisionManager::DeleteInstance();
	ItemManager::DeleteInstance();
	BulletManager::DeleteInstance();
	BattleManager::DeleteInstance();
	//CharacterManager::GetInstance()->ClearRooter();

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->StopBGM(BGM_BATTLE);

	delete m_SkyDome;
}