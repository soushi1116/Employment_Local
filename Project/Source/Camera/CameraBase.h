#pragma once
#include "DxLib.h"
#include "../Floor/Floor.h"

class CharacterBase;
class CollisionSphere;

class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase();

public:
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start() = 0;
	virtual void Step() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Fin() = 0;

	virtual void HitStage(const MV1_COLL_RESULT_POLY_DIM* hitResult) = 0;

public:
	VECTOR GetRot() { return m_Rot; }
	VECTOR GetTarget() { return m_Target; }
	CollisionSphere* GetSphere() { return m_Sphere; }

	void SetRot(VECTOR rot) { m_Rot = rot; }
	void SetTarget(VECTOR target) { m_Target = target; }

	void SetTargetCharacter(CharacterBase* target) { m_TargetCharacter = target; }

protected:
	VECTOR m_Pos;
	VECTOR m_PrevPos;
	VECTOR m_Rot;
	VECTOR m_Target;
	VECTOR m_UpVec;

	CharacterBase* m_TargetCharacter;

	CollisionSphere* m_Sphere;
};