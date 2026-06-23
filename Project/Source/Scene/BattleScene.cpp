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

BattleScene::BattleScene() : SceneBase()
{
	m_TimerFrame = 0;
	m_TimerSecond = 0;
	m_TimerMinute = 0;
}

BattleScene::~BattleScene()
{

}

void BattleScene::Init()
{
	CollisionManager::CreateInstance();

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	CharacterManager* characterManager = CharacterManager::GetInstance();
	characterManager->Init();

	ItemManager::CreateInstance();
	ItemManager* itemManager = ItemManager::GetInstance();
	itemManager->Init();

	CameraManager::CreateInstance();
	CameraManager* cameraManager = CameraManager::GetInstance();
	cameraManager->CreateCamera(CAMERA);
	cameraManager->Init();

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
	CharacterManager::GetInstance()->Start();
	ItemManager::GetInstance()->Start();
	CameraManager::GetInstance()->Start();
	FloorManager::GetInstance()->Start();
	EffekseerManager::GetInstance()->Start();

	CharacterBase* player = CharacterManager::GetInstance()->GetCharacter(PLAYER);

	if (player != nullptr)
	{
		Camera* camera = CameraManager::GetInstance()->GetCamera(CAMERA);
		camera->SetTargetCharacter(player);
	}
}

void BattleScene::Step()
{
	CharacterManager::GetInstance()->Step();
	ItemManager::GetInstance()->Step();
	CameraManager::GetInstance()->Step();
	FloorManager::GetInstance()->Step();
	EffekseerManager::GetInstance()->Step();
	CollisionManager::GetInstance()->CheckCollision();

	if (Input::IsTriggerButton(Input::BUTTON_X))
	{
		SceneManager::GetInstance()->ChangeScene(HOME);
	}

	m_TimerFrame++;

	if (m_TimerFrame >= 60)
	{
		m_TimerSecond++;
		m_TimerFrame = 0;
		CharacterBase* player = CharacterManager::GetInstance()->GetCharacter(PLAYER);
		player->AddSkillPoint();
	}

	if (m_TimerSecond >= 60)
	{
		m_TimerMinute++;
		m_TimerSecond = 0;
	}
}

void BattleScene::Update()
{
	CharacterManager::GetInstance()->Update();
	ItemManager::GetInstance()->Update();
	CameraManager::GetInstance()->Update();
	FloorManager::GetInstance()->Update();
	EffekseerManager::GetInstance()->Update();
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

	CharacterManager::GetInstance()->DrawUI();

	DrawFormatString(750, 50, GetColor(255, 255, 255), "%02d:%02d", m_TimerMinute, m_TimerSecond, TRUE);
}

void BattleScene::Fin()
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	CameraManager::DeleteInstance();
	FloorManager::DeleteInstance();
	CollisionManager::DeleteInstance();
	ItemManager::DeleteInstance();
	CharacterManager::GetInstance()->Fin();
}