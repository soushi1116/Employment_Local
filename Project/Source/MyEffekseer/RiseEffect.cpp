#include "RiseEffect.h"
#include "EffekseerParameter.h"
#include "../MyMath/MyMath.h"

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

