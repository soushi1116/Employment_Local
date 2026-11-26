#pragma once
#include "../Component.h"
#include <memory>
#include <vector>
#include "DxLib.h"

class GameObject;
class CharacterParameter;
class NPCInput;
class Physics3D;

class CharacterAI : public Component
{
public:
	CharacterAI(GameObject* owner);
	~CharacterAI();

public:
	void Start() override;
	void Step() override;

public:
	void SetMoveType(AIMoveType type) { m_MoveType = type; }

	void Track();
	void AvoidObstacle();
	void Attack();
	void Skill();
	void SuperAttack();
	void Escape();
	void GetItem();

	void SearchTarget();

	MV1_COLL_RESULT_POLY_DIM CheckObstacleTarget();
	MV1_COLL_RESULT_POLY_DIM CheckObstaclePos(VECTOR thisPos, VECTOR targetPos);
	
private:
	AIMoveType m_MoveType;
	AIMoveType m_PrevMoveType;

	struct SharedMembers
	{
		std::shared_ptr<CharacterParameter> parameterShared;
		std::shared_ptr<NPCInput> inputShared;
		std::shared_ptr<Physics3D> physicsShared;
		bool isSafety = false;
	};

	std::weak_ptr<CharacterParameter> m_Parameter;
	std::weak_ptr<NPCInput> m_Input;
	std::weak_ptr<Physics3D> m_Physics;

	struct TargetData
	{
		std::weak_ptr<CharacterParameter> parameter;
		std::weak_ptr<Physics3D> physics;
	};

	TargetData m_TargetData;

	SharedMembers CheckMemberPtrs();

	std::vector<VECTOR> m_NodeData;
	// 現在目標にしているノード
	VECTOR m_ActiveNodePos;

	// 次のノードを探す
	bool m_SearchNode;

	void (CharacterAI::* m_StateFunc[AI_MOVE_MAX])(void);
};