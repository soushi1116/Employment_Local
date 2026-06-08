#include "CharacterBase.h"
#include "../MyMath/MyMath.h"

CharacterBase::CharacterBase()
{
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_PrevPos = VGet(0.0f, 0.0f, 0.0f);
	m_Active = false;
	m_Handle = 0;
	m_Gravity = 0.0f;
	m_Type = CHARACTER_TYPE_NONE;
}

CharacterBase::~CharacterBase()
{
	Fin();
}

void CharacterBase::Update()
{
	m_PrevPos = m_Pos;

	m_Pos = MyMath::VecAdd(m_Pos, m_Move);

	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1SetScale(m_Handle, m_Scale);
}

void CharacterBase::Draw()
{
	MV1DrawModel(m_Handle);

	DrawFormatString(0, 0, GetColor(255, 255, 255), "ç¿ïW[%f, %f, %f]", m_Pos.x, m_Pos.y, m_Pos.z);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "âÒì][%f, %f, %f]", m_Rot.x, m_Rot.y, m_Rot.z);
}

void CharacterBase::Fin()
{
	MV1DeleteModel(m_Handle);
}