#include "Beast.h"
#include "../GameObject.h"
#include "CharacterMove.h"
#include "CharacterParameter.h"
#include "../Physics/3DPhysics.h"

Beast::Beast(GameObject* owner) : CharacterMove(owner)
{

}

Beast::~Beast()
{

}

void Beast::Attack()
{
	CharacterMove::Attack();

	
}

void Beast::Skill()
{
	CharacterMove::Skill();


}

void Beast::SuperAttack()
{
	CharacterMove::SuperAttack();


}