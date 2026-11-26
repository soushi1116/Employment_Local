#pragma once
#include "GimmickBase.h"
#include "DxLib.h"
#include <vector>
#include <memory>

class GameObject;

class Conveyor : public GimmickBase
{
public:
	Conveyor(GameObject* owner);
	~Conveyor();

public:
	void Start() override;
	void Update() override;

public:
	void SetLength(float length) { m_Length = length; }
	void SetDirection(VECTOR dir) { m_Direction = dir; }

private:
	VECTOR m_Direction;
	float m_Length;
	std::vector<std::weak_ptr<GameObject>> m_ArrowObjs;
};