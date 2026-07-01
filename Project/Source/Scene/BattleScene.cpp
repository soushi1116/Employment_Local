#include "DxLib.h"
#include "BattleScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Character/CharacterManager.h"
#include "../Camera/CameraManager.h"
#include "../Floor/FloorManager.h"
#include "../ShadowMap/ShadowMap.h"
#include "../Collision/CollisionManager.h"
#include "../MyEffekseer/EffekseerManager.h"
#include "../Item/ItemManager.h"
#include "../Mission/MissionManager.h"
#include "../BattleManager/BattleManager.h"
#include "../UI/UIManager.h"

const VECTOR UI_SKILL_POS = VGet(100.0f, 700.0f, 0.0f);
const VECTOR UI_SUPER_ATTACK_POS = VGet(400.0f, 700.0f, 0.0f);

BattleScene::BattleScene() : SceneBase()
{
	m_ChangeSceneTimer = 0;
}

BattleScene::~BattleScene()
{

}

void BattleScene::Init()
{
	BattleManager::CreateInstance();
	BattleManager* battleManager = BattleManager::GetInstance();
	battleManager->Init();

	CollisionManager::CreateInstance();

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	CharacterManager* characterManager = CharacterManager::GetInstance();
	characterManager->Init();

	ItemManager::CreateInstance();
	ItemManager* itemManager = ItemManager::GetInstance();
	itemManager->Init();

	FloorManager::CreateInstance();
	FloorManager* floorManager = FloorManager::GetInstance();
	floorManager->CreateFloor();
	floorManager->Init();

	ShadowMap::CreateInstance();
	ShadowMap::GetInstance()->Init();

	EffekseerManager::GetInstance()->Init();
}

void BattleScene::Load()
{
	CharacterManager::GetInstance()->Load();
	ItemManager::GetInstance()->Load();
	CameraManager::GetInstance()->Load();
	FloorManager::GetInstance()->Load();
	EffekseerManager::GetInstance()->Load();
}

void BattleScene::Start()
{
	CharacterManager* characterManager = CharacterManager::GetInstance();
	characterManager->Start();

	auto characterList = characterManager->GetCharacterList();
	for (auto character : characterList)
	{
		character->ChangeInBattleScene(true);
	}

	ItemManager::GetInstance()->Start();
	CameraManager* cameraManager = CameraManager::GetInstance();
	cameraManager->Start();
	cameraManager->SetActiveCamera(CAMERA);

	FloorManager::GetInstance()->Start();
	EffekseerManager::GetInstance()->Start();

	CharacterBase* player = CharacterManager::GetInstance()->GetCharacter(PLAYER);

	if (player != nullptr)
	{
		CameraBase* camera = cameraManager->GetCamera(CAMERA);
		camera->SetTargetCharacter(player);
	}

	UIManager* uiManager = UIManager::GetInstance();
	uiManager->CreateUI(UI_SKILL, UI_SKILL_POS);
	uiManager->CreateUI(UI_SUPER_ATTACK, UI_SUPER_ATTACK_POS);
}

void BattleScene::Step()
{
	MissionManager::GetInstance()->Step();
	BattleManager::GetInstance()->Step();
	CharacterManager::GetInstance()->Step();
	ItemManager::GetInstance()->Step();
	CameraManager::GetInstance()->Step();
	FloorManager::GetInstance()->Step();
	EffekseerManager::GetInstance()->Step();
	CollisionManager::GetInstance()->CheckCollision();

	SceneManager* sceneManager = SceneManager::GetInstance();

	if (Input::IsTriggerButton(Input::BUTTON_X))
	{
		sceneManager->ChangeScene(HOME);
	}
}

void BattleScene::Update()
{
	MissionManager::GetInstance()->Update();
	CharacterManager* characterManager = CharacterManager::GetInstance();
	characterManager->Update();
	ItemManager::GetInstance()->Update();
	CameraManager::GetInstance()->Update();
	FloorManager::GetInstance()->Update();
	EffekseerManager::GetInstance()->Update();

	SceneManager* sceneManager = SceneManager::GetInstance();

	if (BattleManager::GetInstance()->IsParentWin())
	{
		m_ChangeSceneTimer++;
		if (m_ChangeSceneTimer > 30)
		{
			characterManager->SetWinnerParent(true);
			sceneManager->ChangeScene(RESULT);
		}
	}

	if (BattleManager::GetInstance()->IsChildWin())
	{
		m_ChangeSceneTimer++;
		if (m_ChangeSceneTimer > 30)
		{
			characterManager->SetWinnerParent(false);
			sceneManager->ChangeScene(RESULT);
		}
	}
}

void BattleScene::Draw()
{
	ShadowMap* shadowMap = ShadowMap::GetInstance();

	shadowMap->StartDrawShadowMap();
	CharacterManager::GetInstance()->DrawModel();
	ItemManager::GetInstance()->Draw();
	shadowMap->EndDrawShadowMap();

	shadowMap->StartAppearsShadowMap();
	FloorManager::GetInstance()->Draw();
	shadowMap->EndAppearsShadowMap();

	CharacterManager::GetInstance()->DrawModel();
	ItemManager::GetInstance()->Draw();
	CameraManager::GetInstance()->Draw();

	CollisionManager::GetInstance()->Draw();

	EffekseerManager::GetInstance()->Draw();

	MissionManager* missionManager = MissionManager::GetInstance();
	auto missionList = missionManager->GetMissionList();

	BattleManager::GetInstance()->Draw();

	for (auto mission : missionList)
	{
		if (mission->IsSelected())
		{
			DrawRotaGraph(1400, 150, 0.3, 0.0, mission->GetHandle(), TRUE);
		}
	}

	CharacterManager::GetInstance()->DrawUI();

	//DrawCircleGauge();

	UIManager::GetInstance()->Draw();
}

void BattleScene::Fin()
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	FloorManager::DeleteInstance();
	CollisionManager::DeleteInstance();
	ItemManager::DeleteInstance();
	BattleManager::DeleteInstance();

	
}