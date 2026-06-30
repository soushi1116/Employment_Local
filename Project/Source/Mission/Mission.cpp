#include "Mission.h"
#include "../Scene/SceneManager.h"
#include "../Scene/BattleScene.h"

const VECTOR DEFAULT_POS = VGet(800.0f, 150.0f, 0.0f);

Mission::Mission()
{
	m_Type = MISSION_TYPE_NONE;
	m_Handle = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_IsSelected = false;
	m_Achieved = false;
}

Mission::~Mission()
{
	Fin();
}

void Mission::Init()
{

}

void Mission::Load()
{
	switch (m_Type)
	{
	case _3_MINUTE:
		m_Handle = LoadGraph("Data/UI/Mission/3minute.png");
		break;
	case _30_SECOND_NO_DAMAGE:
		m_Handle = LoadGraph("Data/UI/Mission/30secondNoDamage.png");
		break;
	case _30_SECOND_NO_MOVE:
		m_Handle = LoadGraph("Data/UI/Mission/30secondNoMove.png");
		break;
	case KILL_10:
		m_Handle = LoadGraph("Data/UI/Mission/Kill10.png");
		break;
	case SUPER_ATTACK_5:
		m_Handle = LoadGraph("Data/UI/Mission/SuperAttack5.png");
		break;
	case MISSION_TYPE_MAX:
		break;
	case MISSION_TYPE_NONE:
		break;
	default:
		break;
	}
}

void Mission::Start()
{
	m_Pos = DEFAULT_POS;
}

void Mission::Step()
{

}

void Mission::Update()
{

}

void Mission::Draw(int index)
{
	if (m_IsSelected)
	{
		DrawRotaGraph(m_Pos.x, m_Pos.y + (float)index * 200.0f, 0.8, 0.0, m_Handle, TRUE);
	}
	else
	{
		DrawRotaGraph(m_Pos.x, m_Pos.y + (float)index * 200.0f, 0.6, 0.0, m_Handle, TRUE);
	}
}

void Mission::Fin()
{
	DeleteGraph(m_Handle);
}