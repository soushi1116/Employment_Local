#include "KillBaster.h"
#include "../BattleManager/BattleManager.h"

const int BORDER_NUM = 1; // ƒNƒŠƒAðŒ

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

	m_BorderNum = BORDER_NUM;

	m_InitNum = BattleManager::GetInstance()->GetKilledNum();
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