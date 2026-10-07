#include "DxLib.h"
#include "DebugScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Character/CharacterManager.h"
#include "../Camera/CameraManager.h"
#include "../Map/MapManager.h"
#include "../ShadowMap/ShadowMap.h"
#include "../Collision/CollisionManager.h"
#include "../MyMath/MyMath.h"
#include "../Bullet/BulletManager.h"
#include "../BattleManager/BattleManager.h"
#include "../MyEffekseer/EffekseerManager.h"
#include "../UI/UIManager.h"
#include "../SkyDome/SkyDome.h"
#include "../Mission/MissionManager.h"
#include "../Item/ItemManager.h"
#include "../FPS/FPSManager.h"

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

	/*MissionManager::CreateInstance();
	MissionManager* missionManager = MissionManager::GetInstance();
	missionManager->Init();*/

	/*BattleManager::CreateInstance();
	BattleManager* battleManager = BattleManager::GetInstance();
	battleManager->Init();*/

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	/*BulletManager::CreateInstance();
	BulletManager* bulletManager = BulletManager::GetInstance();
	bulletManager->Init();*/

	//CharacterManager* characterManager = CharacterManager::GetInstance();
	//characterManager->Init();

	MapManager::CreateInstance();
	MapManager* mapManager = MapManager::GetInstance();
	
	auto map = mapManager->CreateMap(MAP_FACTORY);

	m_SkyDome = new SkyDome;

	ShadowMap::CreateInstance();
	ShadowMap::GetInstance()->Init();

	//EffekseerManager::GetInstance()->Init();

	ItemManager::CreateInstance();
	//ItemManager* itemManager = ItemManager::GetInstance();
	//itemManager->Init();
}

void DebugScene::Load()
{
	//MissionManager::GetInstance()->Load();
	//CharacterManager::GetInstance()->Load();
	//ItemManager::GetInstance()->Load();
	CameraManager::GetInstance()->Load();
	//BulletManager::GetInstance()->Load();
	//EffekseerManager::GetInstance()->Load();
	//BattleManager::GetInstance()->Load();

	m_SkyDome->Load();
}

void DebugScene::Start()
{
	SceneBase::Start();

	//MissionManager::GetInstance()->Start();

	CharacterManager* characterManager = CharacterManager::GetInstance();

	auto characater = characterManager->CreateCharacter(true, true, CharacterType::NINJA);
	//characterManager->CreateCharacter(false, true, ROBOT);
	//characterManager->CreateCharacter(false, true, KNIGHT);
	//characterManager->CreateCharacter(false, true, NINJA);
	//characterManager->SetBossNum(1);

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
	CameraManager::GetInstance()->Step();
	//EffekseerManager::GetInstance()->Step();
	//CharacterManager::GetInstance()->Step();
	ItemManager::GetInstance()->Step();
	//BattleManager::GetInstance()->Step();

	CollisionManager::GetInstance()->CheckCollision();

	SceneManager* sceneManager = SceneManager::GetInstance();

	if (Input::IsTriggerButton(Input::BUTTON_X))
	{
		sceneManager->ChangeScene(HOME);
	}

	m_SkyDome->Step();
}

void DebugScene::Update()
{
	SceneBase::Update();

	//MissionManager::GetInstance()->Update();
	//BulletManager::GetInstance()->Update();
	CameraManager::GetInstance()->Update();
	//CharacterManager::GetInstance()->Update();
	ItemManager::GetInstance()->Update();
	//EffekseerManager::GetInstance()->Update();

	UIManager* uiManager = UIManager::GetInstance();

	FPSSystem* fps = FPSManager::GetInstance()->GetFPS();

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


	//EffekseerManager::GetInstance()->Draw();

	CameraManager::GetInstance()->Draw();

	//MissionManager::GetInstance()->Draw();

	//characterManager->DrawUI();

	//BattleManager::GetInstance()->Draw();

	UIManager::GetInstance()->Draw();

}

void DebugScene::Fin()
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	//MissionManager::DeleteInstance();
	//BulletManager::DeleteInstance();
	MapManager::DeleteInstance();
	CollisionManager::DeleteInstance();
	UIManager::GetInstance()->ResetUI();
	ItemManager::DeleteInstance();
	//CharacterManager::GetInstance()->ClearRooter();

	delete m_SkyDome;
}