#include "DxLib.h"
#include "BattleScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Character/CharacterManager.h"
#include "../Camera/CameraManager.h"
#include "../Floor/FloorManager.h"
#include "../ShadowMap/ShadowMap.h"
#include "../Collision/CollisionManager.h"

BattleScene::BattleScene() : SceneBase()
{
	
}

BattleScene::~BattleScene()
{

}

void BattleScene::Init()
{
	CollisionManager::CreateInstance();

	CharacterManager::CreateInstance();
	CharacterManager* characterManager = CharacterManager::GetInstance();
	characterManager->CreateCharacter(PLAYER);
	characterManager->Init();

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
}

void BattleScene::Load()
{
	CharacterManager::GetInstance()->Load();
	CameraManager::GetInstance()->Load();
	FloorManager::GetInstance()->Load();
}

void BattleScene::Start()
{
	CharacterManager::GetInstance()->Start();
	CameraManager::GetInstance()->Start();
	FloorManager::GetInstance()->Start();
}

void BattleScene::Step()
{
	CharacterManager::GetInstance()->Step();
	CameraManager::GetInstance()->Step();
	FloorManager::GetInstance()->Step();
}

void BattleScene::Update()
{
	CharacterManager::GetInstance()->Update();
	CameraManager::GetInstance()->Update();
	FloorManager::GetInstance()->Update();
}

void BattleScene::Draw()
{
	ShadowMap* shadowMap = ShadowMap::GetInstance();

	shadowMap->StartDrawShadowMap();
	CharacterManager::GetInstance()->Draw();
	shadowMap->EndDrawShadowMap();

	shadowMap->StartAppearsShadowMap();
	FloorManager::GetInstance()->Draw();
	shadowMap->EndAppearsShadowMap();

	CharacterManager::GetInstance()->Draw();
	CameraManager::GetInstance()->Draw();

	CollisionManager::GetInstance()->Draw();
}

void BattleScene::Fin()
{
	CharacterManager::DeleteInstance();
	CameraManager::DeleteInstance();
	FloorManager::DeleteInstance();
	CollisionManager::DeleteInstance();
}