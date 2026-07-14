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
	FloorManager::GetInstance()->Load();
}

void DebugScene::Start()
{
	CameraManager* cameraManager = CameraManager::GetInstance();
	cameraManager->SetActiveCamera(DEBUG_CAMERA);
	cameraManager->Start();

	FloorManager::GetInstance()->Start();

	ChangeLightTypePoint(MyMath::VecZero(), 500.0f, 0.0f, 0.002f, 0.0f);

	SetLightPosition(MyMath::VecY(300.0f));
	SetLightDirection(MyMath::VecX(10.0f));
}

void DebugScene::Step()
{
	CameraManager::GetInstance()->Step();
	FloorManager::GetInstance()->Step();

	SceneManager* sceneManager = SceneManager::GetInstance();

	if (Input::IsTriggerButton(Input::BUTTON_X))
	{
		sceneManager->ChangeScene(HOME);
	}
}

void DebugScene::Update()
{
	CameraManager::GetInstance()->Update();
	FloorManager::GetInstance()->Update();
}

void DebugScene::Draw()
{
	FloorManager::GetInstance()->Draw();

	CameraManager::GetInstance()->Draw();
}

void DebugScene::Fin()
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	FloorManager::DeleteInstance();
	CollisionManager::DeleteInstance();
}