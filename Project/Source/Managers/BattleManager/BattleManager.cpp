#include "DxLib.h"
#include "BattleManager.h"
#include "../CharacterManager/CharacterManager.h"
#include "../../MyColor/MyColor.h"
#include "../../MyMath/MyMath.h"
#include "../../FPS/FPSManager.h"
#include "../../Component/GameObject.h"
#include "../../Component/AllComponents.h"
#include "../RendererManager/RendererManager.h"
#include "../MissionManager/MissionManager.h"
#include "../../Scene/SceneManager.h"

constexpr int TIME_LIMIT_SECOND = 180;

constexpr int TIMER_TEXT_SCALE = 40;

constexpr float TIMER_FRAME_POS_OFFSET = 10.0f;

const VECTOR TIMER_POS = MyMath::Vec2D(800.0f, 70.0f);
const VECTOR TIMER_TEXT_OFFSET = MyMath::Vec2D(-60.0f, -15.0f);

BattleManager* BattleManager::m_Instance = nullptr;

BattleManager::BattleManager()
	:m_BossWin(false)
	, m_ChallengerWin(false)
	, m_NoDamageTimerFrame(0)
	, m_NoDamageTimerSecond(0)
	, m_NoMoveTimerFrame(0)
	, m_NoMoveTimerSecond(0)
	, m_SuperAttackNum(0)
	, m_killedNum(0)
	, m_CurrentMapType(MAP_TYPE_NONE)
	, m_BossMember(MEMBER_NONE)
	,m_TimerFrameHandle (0)
{

}

BattleManager::~BattleManager()
{
	Fin();
}


void BattleManager::Init()
{

}

void BattleManager::Load()
{
	m_TimerFrameHandle = LoadGraph("Data/UI/BattleScene/TimerFrame.png");
}

void BattleManager::Start()
{
	
}


void BattleManager::Step()
{
	auto timerCmpShared = m_TimerCmp.lock();
	auto timerTextShared = m_TimerText.lock();

	if (!timerCmpShared || !timerTextShared) return;

	auto characterList = CharacterManager::GetInstance()->GetCharacters();

	FPSSystem* fps = FPSManager::GetInstance()->GetFPS();

	for (auto& character : characterList)
	{
		auto characterObj = character.lock();

		if (!characterObj) continue;

		auto characterShared = characterObj->GetComponent<CharacterParameter>();

		if (fps->TakeOneSecond())
		{
			characterShared->AddSkillPoint(10);
		}
	}

	int timerMinute = timerCmpShared->GetCurrentMinute();
	int timerSecond = timerCmpShared->GetCurrentSecond();

	char timerText[8];
	snprintf(timerText, sizeof(timerText), "%02d:%02d", timerMinute, timerSecond);

	timerTextShared->SetText(timerText);

	// 十秒おきにミッション発動
	if (timerSecond % 10 == 0 && fps->TakeOneSecond())
	{
		MissionManager::GetInstance()->CreateMission();
	}

	CharacterManager* characterManager = CharacterManager::GetInstance();

	// ボスが倒れたらチャレンジャーの勝ち
	if (!characterManager->IsBossAlive())
	{
		m_ChallengerWin = true;
	}
	// 残り時間が0になったらボスの勝ち
	if (timerCmpShared->IsCountEnd())
	{
		m_BossWin = true;
	}
}

void BattleManager::Update()
{
	
}

void BattleManager::Draw()
{

}

void BattleManager::Fin()
{
	DeleteGraph(m_TimerFrameHandle);
}

void BattleManager::BattleStart()
{
	auto timerObj = std::make_shared<GameObject>();

	std::shared_ptr<SpriteRenderer> frame = timerObj->AddComponent<SpriteRenderer>("Data/UI/BattleScene/TimerFrame.png");
	frame->SetPos(TIMER_POS);
	frame->SetExRate(MyMath::VecSame(1.3f));

	auto timerCmp = timerObj->AddComponent<Timer>();

	timerCmp->CountStart(TIME_LIMIT_SECOND);

	char timerText[6];
	snprintf(timerText, sizeof(timerText), "%02d:%02d", 0, 0);

	auto timerTextRenderer = timerObj->AddComponent<TextRenderer>("");

	timerTextRenderer->SetText(timerText);
	timerTextRenderer->SetFontType(TIMER_TEXT);
	timerTextRenderer->SetPos(VAdd(TIMER_POS, TIMER_TEXT_OFFSET));

	SceneBase* scene = SceneManager::GetInstance()->GetNowScene();
	scene->Instantiate(timerObj);

	m_TimerObj = timerObj;
	m_TimerCmp = timerCmp;
	m_TimerText = timerTextRenderer;
}
