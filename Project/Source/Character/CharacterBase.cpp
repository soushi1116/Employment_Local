#include "CharacterBase.h"

CharacterBase::CharacterBase()
{
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(0.0f, 0.0f, 0.0f);
	m_Active = false;
	m_Handle = 0;
	m_Type = CHARACTER_TYPE_NONE;
}

CharacterBase::~CharacterBase()
{
	Fin();
}

void CharacterBase::Update()
{
	MV1SetPosition(m_Handle, m_Pos);
}

void CharacterBase::Draw()
{
	MV1DrawModel(m_Handle);
}

void CharacterBase::Fin()
{
	MV1DeleteModel(m_Handle);
}