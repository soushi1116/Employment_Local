#include "DxLib.h"
#include "DebugScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Character/CharacterManager.h"
#include "../Camera/CameraManager.h"
#include "../Floor/FloorManager.h"
#include "../ShadowMap/ShadowMap.h"
#include "../Collision/CollisionManager.h"

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
	CharacterManager* characterManager = CharacterManager::GetInstance();

	for (int i = 0; i < CHARACTER_MAX_NUM; i++)
	{
		if (i == characterManager->GetParentNum())
		{
			if (i == 0)
			{
				characterManager->CreateCharacter(true, BOSS);
			}
			else
			{
				characterManager->CreateCharacter(false, BOSS);
			}
		}
		else
		{
			if (i == 0)
			{
				characterManager->CreateCharacter(true, PLAYER);
			}
			else
			{
				characterManager->CreateCharacter(false, PLAYER);
			}
		}
	}

	characterManager->Start();

	auto characterList = characterManager->GetCharacterList();

	for (auto character : characterList)
	{
		character->ChangeInBattleScene(true);
	}

	CameraManager* cameraManager = CameraManager::GetInstance();
	cameraManager->Start();
	cameraManager->SetActiveCamera(CAMERA);

	FloorManager::GetInstance()->Start();

	CharacterBase* player = characterManager->SearchPlayer();
	CameraBase* camera = cameraManager->GetCamera(CAMERA);
	camera->SetTargetCharacter(player);

}

void DebugScene::Step()
{
	CharacterManager::GetInstance()->Step();
	CameraManager::GetInstance()->Step();
	FloorManager::GetInstance()->Step();
	CollisionManager::GetInstance()->CheckCollision();

	SceneManager* sceneManager = SceneManager::GetInstance();

	if (Input::IsTriggerButton(Input::BUTTON_X))
	{
		sceneManager->ChangeScene(HOME);
	}
}

void DebugScene::Update()
{
	CharacterManager* characterManager = CharacterManager::GetInstance();
	characterManager->Update();
	CameraManager::GetInstance()->Update();
	FloorManager::GetInstance()->Update();

	SceneManager* sceneManager = SceneManager::GetInstance();

}

void DebugScene::Draw()
{
	CharacterManager* characterManager = CharacterManager::GetInstance();
	ShadowMap* shadowMap = ShadowMap::GetInstance();

	shadowMap->StartDrawShadowMap();
	characterManager->DrawModel();
	shadowMap->EndDrawShadowMap();

	shadowMap->StartAppearsShadowMap();
	FloorManager::GetInstance()->Draw();
	shadowMap->EndAppearsShadowMap();

	characterManager->DrawModel();
	CameraManager::GetInstance()->Draw();

	CollisionManager::GetInstance()->Draw();

	characterManager->DrawUI();

	CharacterBase* player = characterManager->SearchPlayer();

	double playerSkillPoint = (double)player->GetSkillPoint();
	double playerSuperAttackPoint = (double)player->GetSuperAttackPoint();

}

void DebugScene::Fin()
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	FloorManager::DeleteInstance();
	CollisionManager::DeleteInstance();
}