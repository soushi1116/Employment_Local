#include "CharacterAI.h"
#include "../Component.h"
#include "../GameObject.h"
#include "../../Managers/CharacterManager/CharacterManager.h"

CharacterAI::CharacterAI(GameObject* owner) : Component(owner)
{
	m_MoveType = AI_MOVE_NONE;
}

CharacterAI::~CharacterAI()
{

}

void CharacterAI::Update()
{
	switch (m_MoveType)
	{
	case AI_MOVE_ATTACK:
		AttackMove();
		break;
	case AI_MOVE_ESCAPE:
		EscapeMove();
		break;
	case AI_MOVE_MAX:
		break;
	case AI_MOVE_NONE:
		break;
	default:
		break;
	}
}

void CharacterAI::AttackMove()
{
	std::shared_ptr<GameObject> targetObj = SearchTarget();

	if (targetObj == nullptr) return;
}

void CharacterAI::EscapeMove()
{

}

std::shared_ptr<GameObject> CharacterAI::SearchTarget()
{
	auto parameterShared = m_Parameter.lock();
	auto physicsShared = m_Physics.lock();

	if (!parameterShared) return;

	auto characters = CharacterManager::GetInstance()->GetCharacters();

	float nearestDistance = 10000.0f;

	std::shared_ptr<GameObject> targetCharacter = nullptr;

	for (auto& target : characters)
	{
		auto targetShared = target.lock();

		if (!targetShared) continue;

		std::shared_ptr<CharacterParameter> targetParam = targetShared->GetComponent<CharacterParameter>();
		std::shared_ptr<Physics3D> targetPhysics = targetShared->GetComponent<Physics3D>();

		if (parameterShared->IsBoss() == targetParam->IsBoss()) continue;

		VECTOR thisToTarget = MyMath::VecCreate(physicsShared->GetPos(), targetPhysics->GetPos());
		float thisDistance = VSize(thisToTarget);

		if (thisDistance < nearestDistance)
		{
			targetCharacter = targetShared;
		}
	}

	return targetCharacter;
}