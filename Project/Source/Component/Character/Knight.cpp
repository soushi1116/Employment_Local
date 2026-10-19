#include "Knight.h"
#include "../GameObject.h"
#include "CharacterMove.h"
#include "CharacterParameter.h"
#include "../Physics/3DPhysics.h"

Knight::Knight(GameObject* owner) : CharacterMove(owner)
{

}

Knight::~Knight()
{

}

void Knight::Attack()
{
	CharacterMove::Attack();


}

void Knight::Skill()
{
	CharacterMove::Skill();


}

void Knight::SuperAttack()
{
	CharacterMove::SuperAttack();


}