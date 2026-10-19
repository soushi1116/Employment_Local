#include "PlayerSkillEffect.h"
#include "EffekseerParameter.h"
#include "../MyMath/MyMath.h"

PlayerSkillEffect::PlayerSkillEffect() : EffekseerEffect()
{

}

PlayerSkillEffect::~PlayerSkillEffect()
{
	Fin();
}

void PlayerSkillEffect::Step()
{
	EffekseerEffect::Step();
}

