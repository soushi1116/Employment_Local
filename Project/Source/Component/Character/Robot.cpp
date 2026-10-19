#include "Robot.h"
#include "../GameObject.h"
#include "CharacterMove.h"
#include "CharacterParameter.h"
#include "../Physics/3DPhysics.h"

Robot::Robot(GameObject* owner) : CharacterMove(owner)
{

}

Robot::~Robot()
{

}

void Robot::Attack()
{
	CharacterMove::Attack();


}

void Robot::Skill()
{
	CharacterMove::Skill();


}

void Robot::SuperAttack()
{
	CharacterMove::SuperAttack();


}