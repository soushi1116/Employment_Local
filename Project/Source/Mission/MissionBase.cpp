#include "MissionBase.h"
#include "MissionManager.h"
#include "../Scene/SceneManager.h"
#include "../Scene/BattleScene.h"
//#include "../Character/CharacterManager.h"
#include "../MyMath/MyMath.h"
#include "../Managers/BattleManager/BattleManager.h"
#include "../MyColor/MyColor.h"

// ƒNƒŠƒAðŒ
const int KILL_OPPONENT_BORDER_NUM = 1; // KillOpponent

const VECTOR DEFAULT_POS = VGet(1300.0f, 50.0f, 0.0f);
const int NUM_TEXT_SCALE = 30;

const float HP_HEAL_AMOUNT = 50.0f;
const float POWER_UP_AMOUNT = 1.5f;
const float DEFENCE_UP_AMOUNT = 1.5f;

const int ICON_POS_X_OFFSET = 250;
const int UI_POS_Y_INTERVAL = 100;
const float SIZE_MAGNI = 0.6f;
const float TEXT_POS_X_DIFF = 100.0f;
const float TEXT_POS_Y_DIFF = 15.0f;

MissionBase::MissionBase()
{
	m_Type = MISSION_TYPE_NONE;
	m_Handle = 0;
	m_Pos = MyMath::VecZero();
	m_IsSelected = false;
	m_Achieved = false;
	m_Active = false;
	m_InitNum = 0;
	m_BorderNum = 0;
	m_CurrentNum = 0;
	m_RewardType = REWARD_TYPE_NONE;
	m_RewardAmount = 0.0f;
	//m_NumText = nullptr;
}

MissionBase::~MissionBase()
{
	Fin();
}

void MissionBase::Init()
{

}

void MissionBase::Load()
{

	switch (m_Type)
	{
	case KILL_OPPONENT:
		m_Handle = LoadGraph("Data/UI/Mission/KillOpponent.png");
		break;
	case MISSION_TYPE_MAX:
		break;
	case MISSION_TYPE_NONE:
		break;
	default:
		break;
	}
	
}

void MissionBase::Start()
{
	m_Pos = DEFAULT_POS;
	m_Active = true;

	char numText[4];
	snprintf(numText, sizeof(numText), "%d/%d", m_CurrentNum, m_BorderNum);
	//m_NumText = UIManager::GetInstance()->CreateUIText(numText, MyMath::VecZero(), COLOR_WHITE, MISSION_TEXT);

	m_BorderNum = KILL_OPPONENT_BORDER_NUM;

	m_InitNum = BattleManager::GetInstance()->GetKilledNum();
}

void MissionBase::Step()
{
	m_CurrentNum = BattleManager::GetInstance()->GetKilledNum() - m_InitNum;

	if (m_CurrentNum >= m_BorderNum)
	{
		m_Achieved = true;
		m_Active = false;
	}
}

void MissionBase::Update()
{
	if (m_Achieved)
	{
		//const auto& characterList = CharacterManager::GetInstance()->GetCharacterList();

		/*for (CharacterBase* character : characterList)
		{
			if (character->IsBoss())
			{
				boss = character;
			}
		}*/

		/*switch (m_RewardType)
		{
		case HP_HEAL:
			boss->HPHeal((int)m_RewardAmount);
			break;
		case POWER_UP:
			boss->CreateState(STATE_POWER_UP, 30 * 60);
			boss->AddPowerMagni(m_RewardAmount);
			break;
		case DEFENCE_UP:
			boss->CreateState(STATE_DEFENCE_UP, 30 * 60);
			boss->AddDefenceMagni(m_RewardAmount);
			break;
		case REWARD_TYPE_MAX:
			break;
		case REWARD_TYPE_NONE:
			break;
		default:
			break;
		}*/
	}
}

void MissionBase::Draw(int index)
{
	DrawRotaGraph((int)m_Pos.x, (int)(m_Pos.y + (float)(index * UI_POS_Y_INTERVAL)), SIZE_MAGNI, 0.0, m_Handle, TRUE);

	char numText[4];
	snprintf(numText, sizeof(numText), "%d/%d", m_CurrentNum, m_BorderNum);
	//m_NumText->SetPos(VGet(m_Pos.x + TEXT_POS_X_DIFF, m_Pos.y + (float)(index * UI_POS_Y_INTERVAL) - TEXT_POS_Y_DIFF, 0.0f));
	//m_NumText->SetText(numText);

	auto rewardIconList = MissionManager::GetInstance()->GetRewardIconList();

	switch (m_RewardType)
	{
	case HP_HEAL:
		DrawRotaGraph((int)m_Pos.x + ICON_POS_X_OFFSET, (int)m_Pos.y + index * UI_POS_Y_INTERVAL, SIZE_MAGNI, 0.0, rewardIconList[m_RewardType], TRUE);
		break;
	case POWER_UP:
		DrawRotaGraph((int)m_Pos.x + ICON_POS_X_OFFSET, (int)m_Pos.y + index * UI_POS_Y_INTERVAL, SIZE_MAGNI, 0.0, rewardIconList[m_RewardType], TRUE);
		break;
	case DEFENCE_UP:
		DrawRotaGraph((int)m_Pos.x + ICON_POS_X_OFFSET, (int)m_Pos.y + index * UI_POS_Y_INTERVAL, SIZE_MAGNI, 0.0, rewardIconList[m_RewardType], TRUE);
		break;
	case REWARD_TYPE_MAX:
		break;
	case REWARD_TYPE_NONE:
		break;
	default:
		break;
	}
}

void MissionBase::Fin()
{
	DeleteGraph(m_Handle);
}

void MissionBase::SetRandomReward()
{
	int random = GetRand(REWARD_TYPE_MAX - 1);

	switch (random)
	{
	case 0:
		m_RewardType = HP_HEAL;
		m_RewardAmount = HP_HEAL_AMOUNT;
		break;
	case 1:
		m_RewardType = POWER_UP;
		m_RewardAmount = POWER_UP_AMOUNT;
		break;
	case 2:
		m_RewardType = DEFENCE_UP;
		m_RewardAmount = DEFENCE_UP_AMOUNT;
		break;
	default:
		break;
	}
}