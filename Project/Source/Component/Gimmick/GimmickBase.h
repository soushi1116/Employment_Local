#pragma once
#include "../Component.h"
#include "../../MyEnums/MyEnums.h"
#include <memory>

class GameObject;
class Physics3D;

class GimmickBase : public Component
{
public:
	GimmickBase(GameObject* owner);
	~GimmickBase();

public:
	virtual void Start() = 0;
	virtual void Step() = 0;

public:
	void SetType(GimmickType type) { m_Type = type; }
	GimmickType GetType() const { return m_Type; }

	void SetPhysics(std::weak_ptr<Physics3D> physics) { m_Physics = physics; }

protected:
	GimmickType m_Type;
	std::weak_ptr<Physics3D> m_Physics;
};

