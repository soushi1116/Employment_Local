#include "Cursor.h"
#include "../Input/Input.h"
#include <math.h>
#include "../MyMath/MyMath.h"

Cursor::Cursor()
{
	m_Handle = 0;
	m_Pos = MyMath::VecZero();
	m_MaxPos = MyMath::VecZero();
	m_MinPos = MyMath::VecZero();
	m_Move = MyMath::VecZero();
	m_Scale = 0.0f;
	m_MoveDiff = 0.0f;
	m_IsMoving = false;
}

Cursor::~Cursor()
{
	Fin();
}

void Cursor::Init()
{

}

void Cursor::Load()
{
	m_Handle = LoadGraph("Data/UI/ResultScene/Cursor.png");
}

void Cursor::Start()
{
	
}

void Cursor::Step()
{
	m_Move = MyMath::VecZero();

	int stick = Input::GetLeftStickX();

	if (!m_IsMoving)
	{
		if (stick > 1000 * sinf(DX_PI_F / 4) && m_Pos.x < m_MaxPos.x)
		{
			m_Move.x = m_MoveDiff;
			m_IsMoving = true;
		}
		else if (stick < -1000 * sinf(DX_PI_F / 4) && m_Pos.x > m_MinPos.x)
		{
			m_Move.x = -m_MoveDiff;
			m_IsMoving = true;
		}
	}

	if (stick < 1000 * sinf(DX_PI_F / 4) && stick > -1000 * sinf(DX_PI_F / 4))
	{
		m_IsMoving = false;
	}
}

void Cursor::Update()
{
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);
}

void Cursor::Draw()
{
	DrawRotaGraph((int)m_Pos.x, (int)m_Pos.y, m_Scale, 0.0, m_Handle, TRUE);

	DrawFormatString(0, 0, GetColor(0, 0, 0), "%f", m_Pos.x);
}

void Cursor::Fin()
{
	DeleteGraph(m_Handle);
}
