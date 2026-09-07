#include "KillBaster.h"
#include "../BattleManager/BattleManager.h"

KillBaster::KillBaster() : MissionBase()
{
	
}

KillBaster::~KillBaster()
{

}

void KillBaster::Init()
{

}

void KillBaster::Load()
{
	m_Handle = LoadGraph("Data/UI/Mission/KillBaster.png");
}

void KillBaster::Start()
{
	MissionBase::Start();

	m_BorderNum = 3;

	m_InitNum = BattleManager::GetInstance()->GetKilledNum();

	m_RewardType = HP_HEAL;

	m_RewardAmount = 100.0f;
}

void KillBaster::Step()
{
	m_CurrentNum = BattleManager::GetInstance()->GetKilledNum() - m_InitNum;

	if (m_CurrentNum >= m_BorderNum)
	{
		m_Achieved = true;
		m_Active = false;
	}
}