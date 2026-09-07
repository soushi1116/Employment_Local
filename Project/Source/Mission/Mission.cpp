#include "Mission.h"
#include "../Scene/SceneManager.h"
#include "../Scene/BattleScene.h"
#include "../MyMath/MyMath.h"

const VECTOR DEFAULT_POS = VGet(500.0f, 150.0f, 0.0f);

Mission::Mission()
{
	m_Type = MISSION_TYPE_NONE;
	m_Handle = 0;
	m_Pos = MyMath::VecZero();
	m_IsSelected = false;
	m_Achieved = false;
	m_Active = false;
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
	case KILL_BASTER:
		m_Handle = LoadGraph("Data/UI/Mission/KillBaster.png");
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
	m_Active = true;
}

void Mission::Step()
{

}

void Mission::Update()
{
	if (m_Achieved)
	{
		m_Active = false;
	}
}

void Mission::Draw(int index)
{
	DrawRotaGraph((int)m_Pos.x, (int)(m_Pos.y + (float)index * 200.0f), 0.6, 0.0, m_Handle, TRUE);
}

void Mission::Fin()
{
	DeleteGraph(m_Handle);
}