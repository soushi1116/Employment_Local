#include "EffekseerForDXLib.h"
#include "EffectBase.h"
#include "../../MyMath/MyMath.h"
#include "../../Managers/EffectManager/EffectManager.h"
#include "../Physics/3DPhysics.h"

EffectBase::EffectBase(GameObject* owner)
	: Component(owner)
	, m_Active(false)
	, m_Handle(0)
	, m_Pos(MyMath::VecZero())
	, m_Type(EFFEKSEER_EFFECT_TYPE_NONE)
{

}

EffectBase::~EffectBase()
{
	
}

void EffectBase::Step()
{
	if (!m_Active) return;

	if (IsEffekseer3DEffectPlaying(m_Handle) != 0)
	{
		m_Active = false;
	}

	auto physicsPtr = m_ParentPhysics.lock();

	if (!physicsPtr) return;

	m_Pos = physicsPtr->GetPos();
}

void EffectBase::Update()
{
	if (!m_Active) return;

	SetPosPlayingEffekseer3DEffect(m_Handle, m_Pos.x, m_Pos.y, m_Pos.z);
}

void EffectBase::Play(int handle)
{
	m_Handle = PlayEffekseer3DEffect(handle);
}

void EffectBase::Stop()
{
	StopEffekseer3DEffect(m_Handle);
	m_Active = false;
}