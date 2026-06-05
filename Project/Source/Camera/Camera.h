#pragma once
#include "DxLib.h"

class CharacterBase;

class Camera
{
public:
	Camera();
	~Camera();

public:
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start() = 0;
	virtual void Step() = 0;

	virtual void Update();
	virtual void Draw();
	virtual void Fin();

public:
	VECTOR GetRot() { return m_Rot; }
	VECTOR GetTarget() { return m_Target; }

	void SetRot(VECTOR rot) { m_Rot = rot; }
	void SetTarget(VECTOR target) { m_Target = target; }

protected:
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Target;
	VECTOR m_UpVec;

	CharacterBase* m_TargetCharacter;
};