#include "DxLib.h"
#include "BattleManager.h"
#include "../Character/CharacterManager.h"

BattleManager* BattleManager::m_Instance = nullptr;

BattleManager::BattleManager()
{
	m_PatentWin = false;
	m_ChildWin = false;

	m_TimerFrame = 0;
	m_TimerSecond = 0;
	m_TimerMinute = 0;

	m_NoDamageTimerFrame = 0;
	m_NoDamageTimerSecond = 0;
	m_NoMoveTimerFrame = 0;
	m_NoMoveTimerSecond = 0;

	m_SuperAttackNum = 0;

	m_killedNum = 0;
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

}

void BattleManager::Start()
{
	
}


void BattleManager::Step()
{
	auto characterList = CharacterManager::GetInstance()->GetCharacterList();

	for (auto character : characterList)
	{
		if (character->IsParent())
		{
			m_killedNum = character->GetKilledNum();
		}
	}

	m_TimerFrame++;
	m_NoDamageTimerFrame++;
	m_NoMoveTimerFrame++;

	if (m_TimerFrame >= 60)
	{
		m_TimerSecond++;
		m_TimerFrame = 0;
		CharacterBase* player = CharacterManager::GetInstance()->GetCharacter(PLAYER);
		player->AddSkillPoint();
	}

	if (m_TimerSecond >= 60)
	{
		m_TimerMinute++;
		m_TimerSecond = 0;
	}

	if (m_NoDamageTimerFrame >= 60)
	{
		m_NoDamageTimerSecond++;
		m_NoDamageTimerFrame = 0;
	}

	if (m_NoMoveTimerFrame >= 60)
	{
		m_NoMoveTimerSecond++;
		m_NoMoveTimerFrame = 0;
	}	
}

void BattleManager::Update()
{
	
}

void BattleManager::Draw()
{
	DrawFormatString(750, 50, GetColor(255, 255, 255), "%02d:%02d", m_TimerMinute, m_TimerSecond, TRUE);
	DrawFormatString(750, 100, GetColor(255, 255, 255), "%02d", m_NoDamageTimerSecond, TRUE);
	DrawFormatString(750, 150, GetColor(255, 255, 255), "%02d", m_NoMoveTimerSecond, TRUE);
}

void BattleManager::Fin()
{
	
}


