#include "DxLib.h"
#include "BattleManager.h"
#include "../CharacterManager/CharacterManager.h"
#include "../../Mission/MissionManager.h"
#include "../../MyColor/MyColor.h"
#include "../../MyMath/MyMath.h"
#include "../../FPS/FPSManager.h"
#include "../../Component/GameObject.h"
#include "../../Component/AllComponents.h"
#include "../RendererManager/RendererManager.h"
#include "../../Scene/SceneManager.h"

const float TIME_LIMIT_SECOND = 180.0f;

const int TIMER_TEXT_SCALE = 40;

const float TIMER_FRAME_POS_OFFSET = 10.0f;

const VECTOR TIMER_POS = MyMath::Vec2D(800.0f, 70.0f);
const VECTOR TIMER_TEXT_OFFSET = MyMath::Vec2D(-60.0f, -15.0f);

BattleManager* BattleManager::m_Instance = nullptr;

BattleManager::BattleManager()
{
	m_BossWin = false;
	m_ChallengerWin = false;

	m_TimerSecond = 0;
	m_TimerMinute = 0;
	m_Timer = 0;
	m_EndTime = 0;
	m_TimerFrame = 0.0f;

	m_NoDamageTimerFrame = 0;
	m_NoDamageTimerSecond = 0;
	m_NoMoveTimerFrame = 0;
	m_NoMoveTimerSecond = 0;

	m_SuperAttackNum = 0;

	m_TimerFrameHandle = 0;

	m_killedNum = 0;
	//m_TimerText = nullptr;
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
	m_EndTime = GetNowCount() + TIME_LIMIT_SECOND * 1000;
}


void BattleManager::Step()
{
	FPSSystem* fps = FPSManager::GetInstance()->GetFPS();

	if (!m_BossWin && !m_ChallengerWin)
	{
		//m_TimerSecond -= fps->GetDeltaTime();
	}

	//auto characterList = CharacterManager::GetInstance()->GetCharacterList();

	bool bossWin = true;
	bool challengerWin = true;

	/*for (auto character : characterList)
	{
		if (fps->TakeOneSecond())
		{
			character->AddSkillPoint();
		}

		if (character->IsBoss())
		{
			m_killedNum = character->GetKilledNum();

			if (!character->IsDead())
			{
				challengerWin = false;
			}
		}
		else
		{
			if (!character->IsDead())
			{
				bossWin = false;
			}
		}
	}*/

	m_BossWin = bossWin;
	m_ChallengerWin = challengerWin;

	int nowTime = GetNowCount();

	int milliSecond = m_EndTime - nowTime;

	m_TimerSecond = (milliSecond / 1000) % 60;
	m_TimerMinute = (milliSecond / 1000) / 60;

	char timerText[8];
	snprintf(timerText, sizeof(timerText), "%02d:%02d", m_TimerMinute, m_TimerSecond);

	m_TimerText->SetText(timerText);
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
	char timerText[6];
	snprintf(timerText, sizeof(timerText), "%02d:%02d", m_TimerMinute, m_TimerSecond);

	m_TimerObj = std::make_shared<GameObject>();

	std::shared_ptr<SpriteRenderer> frame = m_TimerObj->AddComponent<SpriteRenderer>("Data/UI/BattleScene/TimerFrame.png");
	frame->SetPos(TIMER_POS);
	frame->SetExRate(MyMath::VecSame(1.3f));

	m_TimerText = m_TimerObj->AddComponent<TextRenderer>();

	m_TimerText->SetText(timerText);
	m_TimerText->SetFontType(TIMER_TEXT);
	m_TimerText->SetPos(VAdd(TIMER_POS, TIMER_TEXT_OFFSET));

	SceneBase* scene = SceneManager::GetInstance()->GetNowScene();
	scene->Instantiate(m_TimerObj);

	
}
