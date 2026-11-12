#pragma once
#include "DxLib.h"
#include "../Component.h"
#include <memory>

class GameObject;
class Physics3D;

const int EFFEKSEER_MAX_PARTICLE = 10000;
const int EFFEKSEER_EFFECT_MAX = 32;

class EffectBase : public Component
{
public:
	EffectBase(GameObject* owner);
	~EffectBase();

public:
	void Step() override;
	void Update() override;

	void Play(int handle);
	void Stop();

	bool IsActive() const { return m_Active; }

	void SetActive(bool active) { m_Active = active; }
	void SetPos(VECTOR pos) { m_Pos = pos; }

	void SetParentPhysics(std::weak_ptr<Physics3D> physics) { m_ParentPhysics = physics; }
	void SetType(EffekseerEffectType type) { m_Type = type; }

	EffekseerEffectType GetType() const { return m_Type; }

protected:
	bool m_Active;
	int m_Handle;
	VECTOR m_Pos;

	std::weak_ptr<Physics3D> m_ParentPhysics;

	EffekseerEffectType m_Type;
};

