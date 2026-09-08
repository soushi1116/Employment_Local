#include "RiseEffect.h"
#include "EffekseerParameter.h"
#include "../MyMath/MyMath.h"
#include "../Bullet/BulletManager.h"
#include "../Bullet/BotBeam.h"

RiseEffect::RiseEffect() : EffekseerEffect()
{

}

RiseEffect::~RiseEffect()
{
	Fin();
}

void RiseEffect::Step()
{
	EffekseerEffect::Step();
}

