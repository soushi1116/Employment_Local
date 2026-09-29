#include "DxLib.h"
#include "BattleManager.h"
#include "../Character/CharacterManager.h"
#include "../Mission/MissionManager.h"
#include "../MyColor/MyColor.h"
#include "../FPS/FPSManager.h"

const int TIME_LIMIT_SECOND = 3 * 60;

const int TIMER_TEXT_SCALE = 40;

const float TIMER_FRAME_POS_OFFSET = 10.0f;

VECTOR const TIMER_POS = MyMath::Vec2D(700.0f, 20.0f);

BattleManager* BattleManager::m_Instance = nullptr;

BattleManager::BattleManager()
{
	m_BossWin = false;
	m_ChallengerWin = false;

	m_TimerSecond = 0;
	m_TimerMinute = 0;

	m_NoDamageTimerFrame = 0;
	m_NoDamageTimerSecond = 0;
	m_NoMoveTimerFrame = 0;
	m_NoMoveTimerSecond = 0;

	m_SuperAttackNum = 0;

	m_TimerFrameHandle = 0;

	m_killedNum = 0;
	m_TimerText = nullptr;
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
	m_TimerSecond = TIME_LIMIT_SECOND;

	char timerText[6];
	snprintf(timerText, sizeof(timerText), "%02d:%02d", m_TimerMinute, m_TimerSecond);
	m_TimerText = UIManager::GetInstance()->CreateUIText(timerText, MyMath::VecZero(), COLOR_BLACK, TIMER_TEXT);
}


void BattleManager::Step()
{
	FPSSystem* fps = FPSManager::GetInstance()->GetFPS();

	if (!m_BossWin && !m_ChallengerWin)
	{
		m_TimerSecond -= fps->GetDeltaTime();
	}

	auto characterList = CharacterManager::GetInstance()->GetCharacterList();

	bool bossWin = true;
	bool challengerWin = true;

	for (auto character : characterList)
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
	}

	m_BossWin = bossWin;
	m_ChallengerWin = challengerWin;

	if (m_TimerSecond >= 60)
	{
		m_TimerMinute++;
		m_TimerSecond -= 60;
	}

	if (m_TimerSecond < 0)
	{
		m_TimerMinute--;
		m_TimerSecond += 60;
	}
}

void BattleManager::Update()
{
	
}

void BattleManager::Draw()
{
	DrawGraph((int)(TIMER_POS.x - TIMER_FRAME_POS_OFFSET), (int)(TIMER_POS.y - TIMER_FRAME_POS_OFFSET), m_TimerFrameHandle, TRUE);

	char timerText[6];
	snprintf(timerText, sizeof(timerText), "%02d:%02d", m_TimerMinute, m_TimerSecond);
	m_TimerText->SetPos(TIMER_POS);
	m_TimerText->SetText(timerText);
}

void BattleManager::Fin()
{
	DeleteGraph(m_TimerFrameHandle);
}


