#pragma once
#include "../Component.h"
#include "../../MyEnums/MyEnums.h"

class GameObject;

class GimmickBase : public Component
{
public:
	GimmickBase(GameObject* owner);
	~GimmickBase();

public:
	virtual void Start() = 0;
	virtual void Update() = 0;

public:
	void SetType(GimmickType type) { m_Type = type; }
	GimmickType GetType() const { return m_Type; }

private:
	GimmickType m_Type;
};

