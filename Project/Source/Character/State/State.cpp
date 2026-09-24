#include "DxLib.h"
#include "State.h"
#include "../CharacterParameter.h"
#include "../../MyMath/MyMath.h"

State::State()
{
	m_Type = STATE_TYPE_NONE;
	m_IconHandle = 0;
	m_Timer = 0;
	m_MaxTime = 0;
	m_Active = false;
	m_Pos = MyMath::VecZero();
}

State::~State()
{
	Fin();
}

void State::Load()
{
	switch (m_Type)
	{
	case STATE_POWER_UP:
		m_IconHandle = LoadGraph("Data/UI/BattleScene/PowerUpIcon.png");
		break;
	case STATE_DEFENCE_UP:
		m_IconHandle = LoadGraph("Data/UI/BattleScene/DefenceUpIcon.png");
		break;
	case STATE_POISONED:
		m_IconHandle = LoadGraph("Data/UI/BattleScene/PoisonIcon.png");
		break;
	case STATE_DESPERATE:
		m_IconHandle = LoadGraph("Data/UI/BattleScene/DesperateIcon.png");
		break;
	case STATE_INVISIBLE:
		m_IconHandle = LoadGraph("Data/UI/BattleScene/InvisibleIcon.png");
		break;
	case STATE_TYPE_MAX:
		break;
	case STATE_TYPE_NONE:
		break;
	default:
		break;
	}
}

void State::Start()
{
	m_Active = true;
	m_Timer = m_MaxTime;
}

void State::Step()
{
	m_Timer--;
}

void State::Update()
{
	if (m_Timer < 0)
	{
		m_Active = false;
	}
}

void State::Draw(int index)
{
	DrawRotaGraph((int)m_Pos.x + index * 70, (int)m_Pos.y, 0.6, 0.0, m_IconHandle, TRUE);
}

void State::Fin()
{
	DeleteGraph(m_IconHandle);
}
