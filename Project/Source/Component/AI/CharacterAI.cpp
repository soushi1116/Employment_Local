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

}

void CharacterAI::EscapeMove()
{

}

void CharacterAI::SearchTarget()
{
	auto parameterShared = m_Parameter.lock();

	if (!parameterShared) return;

	auto characters = CharacterManager::GetInstance()->GetCharacters();

	for (auto& target : characters)
	{
		auto targetShared = target.lock();

		if (!targetShared) continue;

		std::shared_ptr<CharacterParameter> targetParam = targetShared->GetComponent<CharacterParameter>();

		if (parameterShared->GetIndex() == targetParam->GetIndex()) continue;
	}
}