#include "KnightSuperAttackEffect.h"
#include "EffekseerParameter.h"
#include "../MyMath/MyMath.h"
#include "../Character/CharacterManager.h"

KnightSuperAttackEffect::KnightSuperAttackEffect() : EffekseerEffect()
{

}

KnightSuperAttackEffect::~KnightSuperAttackEffect()
{
	Fin();
}

void KnightSuperAttackEffect::Step()
{
	EffekseerEffect::Step();

	if (m_ParentCharacter != nullptr)
	{
		m_Pos = m_ParentCharacter->GetPos();
	}
}

