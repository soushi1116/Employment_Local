#include "DxLib.h"
#include "BattleScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Managers/CharacterManager/CharacterManager.h"
#include "../Managers/CameraManager/CameraManager.h"
#include "../Managers/MapManager/MapManager.h"
#include "../ShadowMap/ShadowMap.h"
#include "../Managers/CollisionManager/CollisionManager.h"
#include "../Managers/ItemManager/ItemManager.h"
#include "../Managers/BattleManager/BattleManager.h"
#include "../Managers/BulletManager/BulletManager.h"
#include "../Managers/EffectManager/EffectManager.h"
#include "../Managers/MissionManager/MissionManager.h"
#include "../MyMath/MyMath.h"
#include "../FPS/FPSManager.h"
#include "../Sound/SoundManager.h"
#include "../SkyDome/SkyDome.h"
#include "../Event/Event.h"
#include "../MyColor/MyColor.h"

const VECTOR UI_RESULT_TEXT_POS = MyMath::Vec2D(800.0f, 200.0f);

BattleScene::BattleScene() : SceneBase()
{
	m_BattleFinishCount = 0;

	m_SkyDome = nullptr;
}

BattleScene::~BattleScene()
{

}

void BattleScene::Init()
{
	MapManager::CreateInstance();

	BattleManager* battleManager = BattleManager::GetInstance();
	battleManager->Init();

	CollisionManager::CreateInstance();

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	ItemManager::CreateInstance();
	ItemManager* itemManager = ItemManager::GetInstance();
	itemManager->Init();

	BulletManager::CreateInstance();
	BulletManager* bulletManager = BulletManager::GetInstance();
	bulletManager->Init();

	m_SkyDome = new SkyDome;

	ShadowMap::CreateInstance();
	ShadowMap::GetInstance()->Init();
}

void BattleScene::Load()
{
	m_SkyDome->Load();
}

void BattleScene::Start()
{
	SceneBase::Start();

	MissionManager::CreateInstance();

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlayBGM(BGM_BATTLE);

	MapManager* mapManager = MapManager::GetInstance();
	BattleManager* battleManager = BattleManager::GetInstance();

	mapManager->CreateMap(battleManager->GetMapType());

	CharacterManager* characterManager = CharacterManager::GetInstance();
	
	for (int i = 0; i < CHARACTER_MAX_NUM; i++)
	{
		CharacterType characterType = characterManager->GetCharacterType(i);

		if (i == characterManager->GetBossNum())
		{
			if (i == 0)
			{
				characterManager->CreateCharacter(true, true, characterType);
			}
			else
			{
				characterManager->CreateCharacter(false, true, characterType);
			}
		}
		else
		{
			if (i == 0)
			{
				characterManager->CreateCharacter(true, true, characterType);
			}
			else
			{
				characterManager->CreateCharacter(false, true, characterType);
			}
		}
	}

	BattleManager::GetInstance()->BattleStart();
	
	BattleManager::GetInstance()->Start();

	DxLib::ChangeLightTypePoint(MyMath::VecZero(), 500.0f, 0.0f, 0.002f, 0.0f);

	DxLib::SetLightPosition(MyMath::VecY(300.0f));
	DxLib::SetLightDirection(MyMath::VecX(10.0f));
}

void BattleScene::Step()
{
	BattleManager* battleManager = BattleManager::GetInstance();
	battleManager->Step();
	ItemManager::GetInstance()->Step();
	BulletManager::GetInstance()->Step();
	CollisionManager::GetInstance()->CheckCollision();

	SceneManager* sceneManager = SceneManager::GetInstance();

	if (Input::IsTriggerButton(Input::BUTTON_X))
	{
		sceneManager->ChangeScene(HOME);
	}

	if (Input::IsTriggerKey(Input::KEY_RIGHT))
	{
		battleManager->BossWin();
	}
	if (Input::IsTriggerKey(Input::KEY_LEFT))
	{
		battleManager->ChallengerWin();
	}

	if (battleManager->IsBossWin() || battleManager->IsChallengerWin())
	{
		if (!m_SceneChangeStart)
		{
			FPSSystem* fps = FPSManager::GetInstance()->GetFPS();
			Event::SetStartCount();

			m_SceneChangeStart = true;

			const char* graphPath = "";

			if (battleManager->IsBossWin())
			{
				graphPath = "Data/UI/BattleScene/BossWin.png";
			}
			else if (battleManager->IsChallengerWin())
			{
				graphPath = "Data/UI/BattleScene/ChallengerWin.png";
			}

			m_ResultText = RendererManager::GetInstance()->CreateUIImage(graphPath, UI_RESULT_TEXT_POS, MyMath::VecSame(1.0f), 0.0f);
			m_ResultText->Start();
		}
	}

	m_SkyDome->Step();
}

void BattleScene::Update()
{
	SceneBase::Update();

	CollisionManager::GetInstance()->CheckCollision();

	for (auto& go : m_GameObjects)
	{
		std::shared_ptr< Physics3D> physics = go->GetComponent<Physics3D>();

		if (physics != nullptr)
		{
			go->ApplyPushBack();
		}
	}

	ItemManager::GetInstance()->Update();
	BulletManager::GetInstance()->Update();
	EffectManager::GetInstance()->Update();

	SceneManager* sceneManager = SceneManager::GetInstance();
	FPSSystem* fps = FPSManager::GetInstance()->GetFPS();

	MissionManager::GetInstance()->Update();

	if (m_SceneChangeEnd)
	{
		BattleManager* battleManager = BattleManager::GetInstance();

		bool isBossWin = battleManager->IsBossWin();
		bool isChallengerWin = battleManager->IsChallengerWin();

		const auto& characters = CharacterManager::GetInstance()->GetCharacters();
		for (auto& character : characters)
		{
			const auto& characterShared = character.lock();

			if (!characterShared) continue;

			const auto& characterParam = characterShared->GetComponent<CharacterParameter>();

			CharacterManager::GetInstance()->AddParametersForResult(characterParam);
		}

		SceneManager::GetInstance()->ChangeScene(RESULT);
	}

	m_SkyDome->Update();
}

void BattleScene::Draw()
{
	m_SkyDome->Draw();

	SceneBase::Draw();

	if (m_SceneChangeStart)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 0, 1600, 900, COLOR_BLACK, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);

		m_ResultText->Draw();
	}
}

void BattleScene::Fin()
{
	SceneBase::Fin();

	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	MissionManager::DeleteInstance();
	MapManager::DeleteInstance();
	CollisionManager::DeleteInstance();
	ItemManager::DeleteInstance();
	BulletManager::DeleteInstance();

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->StopBGM(BGM_BATTLE);

	delete m_SkyDome;
}