#include "DxLib.h"
#include "DebugScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Character/CharacterManager.h"
#include "../Camera/CameraManager.h"
#include "../Floor/FloorManager.h"
#include "../ShadowMap/ShadowMap.h"
#include "../Collision/CollisionManager.h"
#include "../MyMath/MyMath.h"
#include "../Bullet/BulletManager.h"

DebugScene::DebugScene() : SceneBase()
{
}

DebugScene::~DebugScene()
{

}

void DebugScene::Init()
{
	CollisionManager::CreateInstance();

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	BulletManager::CreateInstance();
	BulletManager* bulletManager = BulletManager::GetInstance();
	bulletManager->Init();

	CharacterManager* characterManager = CharacterManager::GetInstance();
	characterManager->Init();

	FloorManager::CreateInstance();
	FloorManager* floorManager = FloorManager::GetInstance();
	floorManager->CreateFloor();
	floorManager->Init();

	ShadowMap::CreateInstance();
	ShadowMap::GetInstance()->Init();

}

void DebugScene::Load()
{
	CharacterManager::GetInstance()->Load();
	CameraManager::GetInstance()->Load();
	BulletManager::GetInstance()->Load();
	FloorManager::GetInstance()->Load();
}

void DebugScene::Start()
{
	CharacterManager* characterManager = CharacterManager::GetInstance();

	characterManager->CreateCharacter(true, NINJA);

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

	FloorManager::GetInstance()->Start();

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
	FloorManager::GetInstance()->Step();
	CharacterManager::GetInstance()->Step();

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
	FloorManager::GetInstance()->Update();
	CharacterManager::GetInstance()->Update();
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
	FloorManager::GetInstance()->Draw();
	shadowMap->EndAppearsShadowMap();

	characterManager->DrawModel();
	BulletManager::GetInstance()->Draw();

	FloorManager::GetInstance()->Draw();

	CameraManager::GetInstance()->Draw();
}

void DebugScene::Fin()
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	BulletManager::DeleteInstance();
	FloorManager::DeleteInstance();
	CollisionManager::DeleteInstance();
}