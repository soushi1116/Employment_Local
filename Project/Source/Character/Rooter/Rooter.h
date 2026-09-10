#pragma once
#include "DxLib.h"

class CharacterBase;
class CollisionSphere;
class MapBase;

class Rooter
{
public:
	Rooter();
	~Rooter();

	void Init();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

	MV1_COLL_RESULT_POLY CheckObstacleTarget();
	MV1_COLL_RESULT_POLY_DIM CheckObstacleForward(bool isRight);

	void SetAvoidRight(bool avoidRight) { m_AvoidRight = avoidRight; }
	void SetActive(bool active) { m_Active = active; }
	void SetPair(Rooter* pair) { m_Pair = pair; }
	void SetParent(CharacterBase* parent) { m_Parent = parent; }
	void SetTarget(CharacterBase* target) { m_Target = target; }

	Rooter* GetPair() { return m_Pair; }
	CharacterBase* GetParent() const{ return m_Parent; }
	bool IsActive() const{ return m_Active; }
	CollisionSphere* GetSphere() { return m_Sphere; }

	void HitStage(MapBase* map);

private:
	VECTOR m_Pos;
	VECTOR m_PrevPos;
	VECTOR m_Rot;
	VECTOR m_MoveDir;
	VECTOR m_Move;

	int m_DirectionChangeTimer;
	int m_LifeTimer;

	float m_Radius;
	float m_Speed;

	bool m_AvoidRight;
	bool m_Active;

	Rooter* m_Pair;

	CharacterBase* m_Target;
	CharacterBase* m_Parent;

	CollisionSphere* m_Sphere;
};

