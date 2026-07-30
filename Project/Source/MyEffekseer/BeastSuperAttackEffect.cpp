#include "BeastSuperAttackEffect.h"
#include "EffekseerParameter.h"
#include "EffekseerForDXLib.h"
#include "../MyMath/MyMath.h"
#include "../Bullet/BulletManager.h"
#include "../Bullet/BotBeam.h"

BeastSuperAttackEffect::BeastSuperAttackEffect() : EffekseerEffect()
{

}

BeastSuperAttackEffect::~BeastSuperAttackEffect()
{
	Fin();
}

void BeastSuperAttackEffect::Step()
{
	EffekseerEffect::Step();

	SetScalePlayingEffekseer3DEffect(m_Handle, 5.0f, 5.0f, 5.0f);
}

