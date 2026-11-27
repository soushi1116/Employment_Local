#include "DxLib.h"
#include "DebugScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Managers/CharacterManager/CharacterManager.h"
#include "../Managers/CameraManager/CameraManager.h"
#include "../Managers/MapManager/MapManager.h"
#include "../ShadowMap/ShadowMap.h"
#include "../Managers/CollisionManager/CollisionManager.h"
#include "../MyMath/MyMath.h"
#include "../Managers/BulletManager/BulletManager.h"
#include "../Managers/BattleManager/BattleManager.h"
#include "../Managers/EffectManager/EffectManager.h"
#include "../SkyDome/SkyDome.h"
#include "../Managers/MissionManager/MissionManager.h"
#include "../Managers/ItemManager/ItemManager.h"
#include "../Managers/GimmickManager/GimmickManager.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"
#include "../MyColor/MyColor.h"

const VECTOR UI_RESULT_TEXT_POS = MyMath::Vec2D(800.0f, 200.0f);

DebugScene::DebugScene()
	: SceneBase()
	, m_BattleFinishCountDebug(0)
	, m_SkyDome(nullptr)
{
	
}

DebugScene::~DebugScene()
{

}

void DebugScene::Init()
{
	m_GameObjects.clear();

	CollisionManager::CreateInstance();

	MissionManager::CreateInstance();

	BattleManager::CreateInstance();
	BattleManager* battleManager = BattleManager::GetInstance();
	battleManager->Init();

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	BulletManager::CreateInstance();

	MapManager::CreateInstance();
	MapManager* mapManager = MapManager::GetInstance();

	GimmickManager::CreateInstance();
	GimmickManager::GetInstance()->Start();
	
	auto map = mapManager->CreateMap(MAP_FACTORY);

	m_SkyDome = new SkyDome;

	ShadowMap::GetInstance()->Init();

	EffectManager::GetInstance()->Init();

	ItemManager::CreateInstance();
}

void DebugScene::Load()
{
	EffectManager::GetInstance()->Load();

	m_SkyDome->Load();
}

void DebugScene::Start()
{
	SceneBase::Start();

	CharacterManager* characterManager = CharacterManager::GetInstance();

	BattleManager::GetInstance()->SetBossMember(OPPONENT_1);

	characterManager->CreateCharacter(true, true, CharacterType::KNIGHT);
	characterManager->CreateCharacter(false, true, CharacterType::ROBOT);	
	//characterManager->CreateCharacter(false, true, CharacterType::FAIRY);
	//characterManager->CreateCharacter(false, true, CharacterType::NINJA);
	//characterManager->SetBossNum(1);

	BattleManager::GetInstance()->BattleStart();

	ChangeLightTypePoint(MyMath::VecZero(), 5000.0f, 0.0f, 0.002f, 0.0f);

	SetLightPosition(MyMath::VecY(300.0f));
	SetLightDirection(MyMath::VecX(10.0f));
}

void DebugScene::Step()
{
	EffectManager::GetInstance()->Step();
	ItemManager::GetInstance()->Step();
	BattleManager::GetInstance()->Step();

	SceneManager* sceneManager = SceneManager::GetInstance();

	if (Input::IsTriggerButton(Input::BUTTON_X))
	{
		sceneManager->ChangeScene(HOME);
	}

	BattleManager* battleManager = BattleManager::GetInstance();

#ifdef _DEBUG
	// デバッグ用コマンド
	// ボスの勝ち
	if (Input::IsTriggerKey(Input::KEY_LEFT))
	{
		battleManager->BossWin();
	}
	// チャレンジャーの勝ち
	if (Input::IsTriggerKey(Input::KEY_RIGHT))
	{
		battleManager->ChallengerWin();
	}
	// ミッション発動
	if (Input::IsTriggerKey(Input::KEY_UP))
	{
		MissionManager::GetInstance()->CreateMission();
	}
#endif

	

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

void DebugScene::Update()
{
	SceneBase::Update();

	CollisionManager::GetInstance()->CheckCollision();

	for (auto& go : m_GameObjects)
	{
		go->ApplyPushBack();
	}

	ItemManager::GetInstance()->Update();
	EffectManager::GetInstance()->Update();

	MissionManager::GetInstance()->Update();

	FPSSystem* fps = FPSManager::GetInstance()->GetFPS();

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

	BulletManager::GetInstance()->Update();
}

void DebugScene::Draw()
{
	SceneBase::Draw();

	if (m_SceneChangeStart)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 0, 1600, 900, COLOR_BLACK, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);

		m_ResultText->Draw();
	}
}

void DebugScene::Fin()
{
	SceneBase::Fin();

	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	MapManager::DeleteInstance();
	CollisionManager::DeleteInstance();
	ItemManager::DeleteInstance();
	MissionManager::DeleteInstance();

	delete m_SkyDome;
}