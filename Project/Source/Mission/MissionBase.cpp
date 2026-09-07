#include "MissionBase.h"
#include "../Scene/SceneManager.h"
#include "../Scene/BattleScene.h"
#include "../Character/CharacterManager.h"
#include "../MyMath/MyMath.h"

const VECTOR DEFAULT_POS = VGet(1200.0f, 100.0f, 0.0f);
const int NUM_TEXT_SCALE = 30;

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
	m_NumText = nullptr;
}

MissionBase::~MissionBase()
{
	Fin();
}

void MissionBase::Start()
{
	m_Pos = DEFAULT_POS;
	m_Active = true;

	char numText[3];
	snprintf(numText, sizeof(numText), "%d/%d", m_CurrentNum, m_BorderNum);
	m_NumText = UIManager::GetInstance()->CreateUIText(numText, MyMath::VecZero(), GetColor(255, 255, 255), NUM_TEXT_SCALE);
}

void MissionBase::Update()
{
	if (m_Achieved)
	{
		const auto& characterList = CharacterManager::GetInstance()->GetCharacterList();

		CharacterBase* boss = nullptr;

		for (CharacterBase* character : characterList)
		{
			if (character->IsBoss())
			{
				boss = character;
			}
		}

		switch (m_RewardType)
		{
		case HP_HEAL:
			boss->HPHeal((int)m_RewardAmount);
			break;
		case POWER_UP:
			break;
		case REWARD_TYPE_MAX:
			break;
		case REWARD_TYPE_NONE:
			break;
		default:
			break;
		}
	}
}

void MissionBase::Draw(int index)
{
	DrawRotaGraph((int)m_Pos.x, (int)(m_Pos.y + (float)index * 100.0f), 0.6, 0.0, m_Handle, TRUE);

	char numText[4];
	snprintf(numText, sizeof(numText), "%d/%d", m_CurrentNum, m_BorderNum);
	m_NumText->SetPos(VGet(m_Pos.x + 100.0f, m_Pos.y + index * 100.0f - 15.0f, 0.0f));
	m_NumText->SetText(numText);
}

void MissionBase::Fin()
{
	DeleteGraph(m_Handle);
}