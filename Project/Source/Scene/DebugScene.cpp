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

DebugScene::DebugScene() : SceneBase()
{
	
}

DebugScene::~DebugScene()
{

}

void DebugScene::Init()
{
	CollisionManager::CreateInstance();

	BattleManager::CreateInstance();
	BattleManager* battleManager = BattleManager::GetInstance();
	battleManager->Init();

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	BulletManager::CreateInstance();
	BulletManager* bulletManager = BulletManager::GetInstance();
	bulletManager->Init();

	CharacterManager* characterManager = CharacterManager::GetInstance();
	characterManager->Init();

	MapManager::CreateInstance();
	MapManager* mapManager = MapManager::GetInstance();
	mapManager->CreateMap();
	mapManager->Init();

	ShadowMap::CreateInstance();
	ShadowMap::GetInstance()->Init();

	EffekseerManager::GetInstance()->Init();
}

void DebugScene::Load()
{
	CharacterManager::GetInstance()->Load();
	CameraManager::GetInstance()->Load();
	BulletManager::GetInstance()->Load();
	MapManager::GetInstance()->Load();
	EffekseerManager::GetInstance()->Load();
}

void DebugScene::Start()
{
	CharacterManager* characterManager = CharacterManager::GetInstance();

	characterManager->CreateCharacter(true, ROBOT);
	characterManager->CreateCharacter(false, KNIGHT);

	characterManager->Start();

	auto characterList = characterManager->GetCharacterList();

	for (auto character : characterList)
	{
		character->ChangeInBattleScene(true);
	}

	CameraManager* cameraManager = CameraManager::GetInstance();
	cameraManager->SetActiveCamera(CAMERA);
	cameraManager->Start();

	BulletManager::CreateInstance();
	BulletManager* bulletManager = BulletManager::GetInstance();
	bulletManager->Init();

	BulletManager::GetInstance()->Start();

	MapManager::GetInstance()->Start();

	EffekseerManager::GetInstance()->Start();

	CharacterBase* player = characterManager->SearchPlayer();
	CameraBase* camera = cameraManager->GetCamera(CAMERA);
	camera->SetTargetCharacter(player);

	ChangeLightTypePoint(MyMath::VecZero(), 5000.0f, 0.0f, 0.002f, 0.0f);

	SetLightPosition(MyMath::VecY(300.0f));
	SetLightDirection(MyMath::VecX(10.0f));
}

void DebugScene::Step()
{
	BulletManager::GetInstance()->Step();
	CameraManager::GetInstance()->Step();
	MapManager::GetInstance()->Step();
	EffekseerManager::GetInstance()->Step();
	CharacterManager::GetInstance()->Step();
	BattleManager::GetInstance()->Step();

	CollisionManager::GetInstance()->CheckCollision();

	SceneManager* sceneManager = SceneManager::GetInstance();

	if (Input::IsTriggerButton(Input::BUTTON_X))
	{
		sceneManager->ChangeScene(HOME);
	}
}

void DebugScene::Update()
{
	BulletManager::GetInstance()->Update();
	CameraManager::GetInstance()->Update();
	MapManager::GetInstance()->Update();
	CharacterManager::GetInstance()->Update();
	EffekseerManager::GetInstance()->Update();
}

void DebugScene::Draw()
{
	CharacterManager* characterManager = CharacterManager::GetInstance();
	ShadowMap* shadowMap = ShadowMap::GetInstance();

	shadowMap->StartDrawShadowMap();
	characterManager->DrawModel();
	BulletManager::GetInstance()->Draw();
	shadowMap->EndDrawShadowMap();

	shadowMap->StartAppearsShadowMap();
	MapManager::GetInstance()->Draw();
	shadowMap->EndAppearsShadowMap();

	characterManager->DrawModel();
	BulletManager::GetInstance()->Draw();

	CollisionManager::GetInstance()->Draw();

	MapManager::GetInstance()->Draw();

	EffekseerManager::GetInstance()->Draw();

	CameraManager::GetInstance()->Draw();

	characterManager->DrawUI();

	MapManager::GetInstance()->DrawImage();
}

void DebugScene::Fin()
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	BulletManager::DeleteInstance();
	MapManager::DeleteInstance();
	CollisionManager::DeleteInstance();
	EffekseerManager::DeleteInstance();
}