#include "EffekseerForDXLib.h"
#include "EffekseerEffect.h"
#include "../MyMath/MyMath.h"

EffekseerEffect::EffekseerEffect()
{
	m_Active = false;
	m_Handle = 0;
	m_Pos = MyMath::VecZero();
	m_ParentBullet = nullptr;
	m_ParentCharacter = nullptr;
	m_Type = EFFEKSEER_EFFECT_TYPE_NONE;
}

EffekseerEffect::~EffekseerEffect()
{
	Fin();
}

void EffekseerEffect::Step()
{
	if (IsEffekseer3DEffectPlaying(m_Handle) != 0)
	{
		m_Active = false;
	}
}

void EffekseerEffect::Update()
{
	if (!m_Active) return;

	SetPosPlayingEffekseer3DEffect(m_Handle, m_Pos.x, m_Pos.y, m_Pos.z);
}

void EffekseerEffect::Fin()
{
	
}

void EffekseerEffect::Play(int handle)
{
	m_Handle = PlayEffekseer3DEffect(handle);
}

void EffekseerEffect::Stop()
{
	StopEffekseer3DEffect(m_Handle);
	m_Active = false;
}