#include "Fairy.h"
#include "../GameObject.h"
#include "CharacterMove.h"
#include "CharacterParameter.h"
#include "../Physics/3DPhysics.h"

Fairy::Fairy(GameObject* owner) : CharacterMove(owner)
{

}

Fairy::~Fairy()
{

}

void Fairy::Attack()
{
	CharacterMove::Attack();


}

void Fairy::Skill()
{
	CharacterMove::Skill();


}

void Fairy::SuperAttack()
{
	CharacterMove::SuperAttack();


}