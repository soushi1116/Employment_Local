#include "BeastSuperAttackEffect.h"
#include "EffekseerParameter.h"
#include "../MyMath/MyMath.h"
#include "../Bullet/BulletManager.h"
#include "../Bullet/BotBeam.h"

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

