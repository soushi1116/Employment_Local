#include "DxLib.h"
#include "BattleScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Character/CharacterManager.h"
#include "../Camera/CameraManager.h"
#include "../Map/MapManager.h"
#include "../ShadowMap/ShadowMap.h"
#include "../Collision/CollisionManager.h"
#include "../MyEffekseer/EffekseerManager.h"
#include "../Item/ItemManager.h"
#include "../Mission/MissionManager.h"
#include "../BattleManager/BattleManager.h"
#include "../UI/UIManager.h"
#include "../Bullet/BulletManager.h"
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

	BulletManager::CreateInstance();
	BulletManager* bulletManager = BulletManager::GetInstance();
	bulletManager->Init();

	m_SkyDome = new SkyDome;

	ShadowMap::CreateInstance();
	ShadowMap::GetInstance()->Init();

	EffekseerManager::GetInstance()->Init();
}

void BattleScene::Load()
{
	CharacterManager::GetInstance()->Load();
	ItemManager::GetInstance()->Load();
	BulletManager::GetInstance()->Load();
	CameraManager::GetInstance()->Load();
	MapManager::GetInstance()->Load();
	EffekseerManager::GetInstance()->Load();

	m_SkyDome->Load();
}

void BattleScene::Start()
{
	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlayBGM(BGM_BATTLE);

	CharacterManager* characterManager = CharacterManager::GetInstance();
	
	for (int i = 0; i < CHARACTER_MAX_NUM; i++)
	{
		CharacterType characterType = characterManager->GetCharacterType(i);

		if (i == characterManager->GetBossNum())
		{
			if (i == 0)
			{
				characterManager->CreateCharacter(true, characterType);
			}
			else
			{
				characterManager->CreateCharacter(false, characterType);
			}
		}
		else
		{
			if (i == 0)
			{
				characterManager->CreateCharacter(true, characterType);
			}
			else
			{
				characterManager->CreateCharacter(false, characterType);
			}
		}
	}
	
	characterManager->Start();

	auto characterList = characterManager->GetCharacterList();
	
	for (auto character : characterList)
	{
		character->ChangeInBattleScene(true);
	}

	ItemManager::GetInstance()->Start();
	BulletManager::GetInstance()->Start();

	CameraManager* cameraManager = CameraManager::GetInstance();
	cameraManager->SetActiveCamera(CAMERA);
	cameraManager->Start();

	MapManager::GetInstance()->Start();
	EffekseerManager::GetInstance()->Start();

	CharacterBase* player = characterManager->SearchPlayer();
	CameraBase* camera = cameraManager->GetCamera(CAMERA);
	camera->SetTargetCharacter(player);

	BattleManager::GetInstance()->Start();

	DxLib::ChangeLightTypePoint(MyMath::VecZero(), 500.0f, 0.0f, 0.002f, 0.0f);

	DxLib::SetLightPosition(MyMath::VecY(300.0f));
	DxLib::SetLightDirection(MyMath::VecX(10.0f));
}

void BattleScene::Step()
{
	MissionManager::GetInstance()->Step();
	BattleManager::GetInstance()->Step();
	CharacterManager::GetInstance()->Step();
	ItemManager::GetInstance()->Step();
	BulletManager::GetInstance()->Step();
	CameraManager::GetInstance()->Step();
	MapManager::GetInstance()->Step();
	EffekseerManager::GetInstance()->Step();
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
	MissionManager::GetInstance()->Update();
	CharacterManager* characterManager = CharacterManager::GetInstance();
	characterManager->Update();
	ItemManager::GetInstance()->Update();
	BulletManager::GetInstance()->Update();
	CameraManager::GetInstance()->Update();
	MapManager::GetInstance()->Update();
	EffekseerManager::GetInstance()->Update();

	SceneManager* sceneManager = SceneManager::GetInstance();
	FPSSystem* fps = FPSManager::GetInstance()->GetFPS();

	if (!m_BattleFinished)
	{
		if (BattleManager::GetInstance()->IsBossWin())
		{
			m_BattleFinished = true;
			m_BattleFinishCount = fps->GetDeltaTime();
			characterManager->SetWinnerBoss(true);
		}

		if (BattleManager::GetInstance()->IsChildWin())
		{
			m_BattleFinished = true;
			m_BattleFinishCount = fps->GetDeltaTime();
			characterManager->SetWinnerBoss(false);
		}
	}
	else
	{
		if (fps->GetDeltaTime() - m_BattleFinishCount > 3)
		{
			sceneManager->ChangeScene(RESULT);
		}
	}

	m_SkyDome->Update();
}

void BattleScene::Draw()
{
	if (m_BattleFinished)
	{
		SetDrawBright(128, 128, 128);
	}

	m_SkyDome->Draw();

	CharacterManager* characterManager = CharacterManager::GetInstance();
	ShadowMap* shadowMap = ShadowMap::GetInstance();

	shadowMap->StartDrawShadowMap();
	characterManager->DrawModel();
	ItemManager::GetInstance()->Draw();
	BulletManager::GetInstance()->Draw();
	shadowMap->EndDrawShadowMap();

	shadowMap->StartAppearsShadowMap();
	MapManager::GetInstance()->Draw();
	shadowMap->EndAppearsShadowMap();

	characterManager->DrawModel();
	ItemManager::GetInstance()->Draw();
	BulletManager::GetInstance()->Draw();
	CameraManager::GetInstance()->Draw();

	CollisionManager::GetInstance()->Draw();

	EffekseerManager::GetInstance()->Draw();

	BattleManager::GetInstance()->Draw();

	// Bossの場合のみ選択したミッションを表示
	MissionManager* missionManager = MissionManager::GetInstance();
	auto missionList = missionManager->GetMissionList();

	int bossNum = characterManager->GetBossNum();

	if (bossNum == 0)
	{
		for (auto mission : missionList)
		{
			if (mission->IsSelected())
			{
				DrawRotaGraph(1400, 150, 0.3, 0.0, mission->GetHandle(), TRUE);
			}
		}
	}

	characterManager->DrawUI();

	SetDrawBright(255, 255, 255);

	UIManager::GetInstance()->Draw();

	MapManager::GetInstance()->DrawImage();
}

void BattleScene::Fin()
{
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	MapManager::DeleteInstance();
	CollisionManager::DeleteInstance();
	ItemManager::DeleteInstance();
	BulletManager::DeleteInstance();
	BattleManager::DeleteInstance();
	UIManager::GetInstance()->ResetUI();

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->StopBGM(BGM_BATTLE);

	delete m_SkyDome;
}