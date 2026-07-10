#include "BotBeamEffect.h"
#include "EffekseerParameter.h"
#include "../MyMath/MyMath.h"
#include "../Bullet/BulletManager.h"
#include "../Bullet/BotBeam.h"

BotBeamEffect::BotBeamEffect() : EffekseerEffect()
{
	
}

BotBeamEffect::~BotBeamEffect()
{
	Fin();
}

void BotBeamEffect::Step()
{
	EffekseerEffect::Step();

	if (m_ParentBullet != nullptr)
	{
		m_Pos = m_ParentBullet->GetPos();
	}
}

