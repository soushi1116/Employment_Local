#pragma once
#include "../Component.h"
#include <memory>

class GameObject;
class CharacterParameter;
class NPCInput;

enum AIMoveType
{
	AI_MOVE_ATTACK,
	AI_MOVE_ESCAPE,

	AI_MOVE_MAX,
	AI_MOVE_NONE = -1
};

class CharacterAI : public Component
{
public:
	CharacterAI(GameObject* owner);
	~CharacterAI();

public:
	void Update() override;

public:
	void SetMoveType(AIMoveType type) { m_MoveType = type; }

	void AttackMove();
	void EscapeMove();

	void SearchTarget();

private:
	AIMoveType m_MoveType;
	std::weak_ptr<CharacterParameter> m_Parameter;
	std::weak_ptr<NPCInput> m_Input;
};