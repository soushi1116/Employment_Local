#pragma once
#include "../Component.h"
#include <memory>
#include <vector>
#include "DxLib.h"

class GameObject;
class CharacterParameter;
class NPCInput;
class Physics3D;
//class Timer;

enum AIMoveType
{
	AI_MOVE_TRACK,
	AI_MOVE_AVOID_OBSTACLE,
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
	void Start() override;
	void Step() override;

public:
	void SetMoveType(AIMoveType type) { m_MoveType = type; }
	//void SetIsRooter(bool isRooter) { m_IsRooter = isRooter; }
	//void SetTimer(std::weak_ptr<Timer> timer) { m_Timer = timer; }

	//bool IsRooterArchive() const { return m_IsRooterArchive; }

	void Track();
	void AvoidObstacle();
	void Attack();
	void Escape();

	void SearchTarget();

	MV1_COLL_RESULT_POLY_DIM CheckObstacleTarget();
	MV1_COLL_RESULT_POLY_DIM CheckObstaclePos(VECTOR thisPos, VECTOR targetPos);
	

	//void CreateRooter(bool isRight);

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
	VECTOR m_ActiveNodePos;
	bool m_SearchNode;
};