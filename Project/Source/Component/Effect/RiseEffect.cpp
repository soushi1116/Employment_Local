#include "RiseEffect.h"
#include "../GameObject.h"

RiseEffect::RiseEffect(GameObject* owner) : EffectBase(owner)
{

}

RiseEffect::~RiseEffect()
{
	
}

void RiseEffect::Step()
{
	EffectBase::Step();
}

