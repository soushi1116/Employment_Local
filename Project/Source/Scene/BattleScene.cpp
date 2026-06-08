#include "DxLib.h"
#include "BattleScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Character/CharacterManager.h"
#include "../Camera/CameraManager.h"
#include "../Floor/Floor.h"
#include "../ShadowMap/ShadowMap.h"

BattleScene::BattleScene() : SceneBase()
{
	m_Floor = nullptr;
}

BattleScene::~BattleScene()
{

}

void BattleScene::Init()
{
	CharacterManager::CreateInstance();
	CharacterManager* characterManager = CharacterManager::GetInstance();
	characterManager->CreateCharacter(PLAYER);
	characterManager->Init();

	CameraManager::CreateInstance();
	CameraManager* cameraManager = CameraManager::GetInstance();
	cameraManager->CreateCamera(CAMERA);
	cameraManager->Init();

	m_Floor = new Floor;
	m_Floor->Init();

	ShadowMap::CreateInstance();
	ShadowMap::GetInstance()->Init();
}

void BattleScene::Load()
{
	CharacterManager::GetInstance()->Load();
	CameraManager::GetInstance()->Load();
	m_Floor->Load();
}

void BattleScene::Start()
{
	CharacterManager::GetInstance()->Start();
	CameraManager::GetInstance()->Start();
	m_Floor->Start();
}

void BattleScene::Step()
{
	CharacterManager::GetInstance()->Step();
	CameraManager::GetInstance()->Step();
	m_Floor->Step();
}

void BattleScene::Update()
{
	CharacterManager::GetInstance()->Update();
	CameraManager::GetInstance()->Update();
	m_Floor->Update();
}

void BattleScene::Draw()
{
	ShadowMap* shadowMap = ShadowMap::GetInstance();

	shadowMap->StartDrawShadowMap();
	CharacterManager::GetInstance()->Draw();
	shadowMap->EndDrawShadowMap();

	shadowMap->StartAppearsShadowMap();
	m_Floor->Draw();
	shadowMap->EndAppearsShadowMap();

	CharacterManager::GetInstance()->Draw();
	CameraManager::GetInstance()->Draw();	
}

void BattleScene::Fin()
{
	CharacterManager::DeleteInstance();
	CameraManager::DeleteInstance();
	delete m_Floor;
}