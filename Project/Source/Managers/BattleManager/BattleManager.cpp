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

	m_NoDamageTimerFrame = 0;
	m_NoDamageTimerSecond = 0;
	m_NoMoveTimerFrame = 0;
	m_NoMoveTimerSecond = 0;

	m_SuperAttackNum = 0;

	m_TimerFrameHandle = 0;

	m_killedNum = 0;
	m_CurrentMapType = MAP_TYPE_NONE;

	m_BossMember = MEMBER_NONE;
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

	int timerMinute = m_TimerCmp->GetCurrentMinute();
	int timerSecond = m_TimerCmp->GetCurrentSecond();

	char timerText[8];
	snprintf(timerText, sizeof(timerText), "%02d:%02d", timerMinute, timerSecond);

	m_TimerText->SetText(timerText);

	CharacterManager* characterManager = CharacterManager::GetInstance();

	if (!characterManager->IsAlive(true))
	{
		m_ChallengerWin = true;
	}
	else if (!characterManager->IsAlive(false))
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
	m_TimerObj = std::make_shared<GameObject>();

	std::shared_ptr<SpriteRenderer> frame = m_TimerObj->AddComponent<SpriteRenderer>("Data/UI/BattleScene/TimerFrame.png");
	frame->SetPos(TIMER_POS);
	frame->SetExRate(MyMath::VecSame(1.3f));

	m_TimerCmp = m_TimerObj->AddComponent<Timer>();

	m_TimerCmp->CountStart(TIME_LIMIT_SECOND);

	char timerText[6];
	snprintf(timerText, sizeof(timerText), "%02d:%02d", 0, 0);

	m_TimerText = m_TimerObj->AddComponent<TextRenderer>();

	m_TimerText->SetText(timerText);
	m_TimerText->SetFontType(TIMER_TEXT);
	m_TimerText->SetPos(VAdd(TIMER_POS, TIMER_TEXT_OFFSET));

	SceneBase* scene = SceneManager::GetInstance()->GetNowScene();
	scene->Instantiate(m_TimerObj);

	
}
