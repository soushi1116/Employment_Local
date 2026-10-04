#pragma once

#include "DxLib.h"
#include "../../../MyMath/MyMath.h"
#include "../../../Collision/CollisionParameter.h"
#include "CollisionBase.h"

class BoxCollision : public CollisionBase
{
public:
	BoxCollision(GameObject* owner);
	~BoxCollision();

	void Draw() override;

	void SetTargetPos(VECTOR* targetPos) { m_TargetPos = targetPos; }
	void SetLocalPos(VECTOR localPos) { m_LocalPos = localPos; }
	void SetSize(VECTOR size) { m_Size = size; }

	void MultSize(VECTOR mult);

	VECTOR GetPos() { return MyMath::VecAdd(*m_TargetPos, m_LocalPos); }
	VECTOR GetTargetPos() const { return *m_TargetPos; }
	VECTOR GetLocalPos() const { return m_LocalPos; }
	VECTOR GetSize() const { return m_Size; }

	/*float GetLeft() { return (m_TargetPos->x + m_LocalPos.x) - m_Size.x * 0.5f; }
	float GetRight() { return (m_TargetPos->x + m_LocalPos.x) + m_Size.x * 0.5f; }
	float GetTop() { return (m_TargetPos->y + m_LocalPos.y) + m_Size.y * 0.5f; }
	float GetBottom() { return (m_TargetPos->y + m_LocalPos.y) - m_Size.y * 0.5f; }
	float GetFront() { return (m_TargetPos->z + m_LocalPos.z) - m_Size.z * 0.5f; }
	float GetBack() { return (m_TargetPos->z + m_LocalPos.z) + m_Size.z * 0.5f; }*/

	float GetLeft() { return m_Pos.x - m_Size.x * 0.5f; }
	float GetRight() { return m_Pos.x + m_Size.x * 0.5f; }
	float GetTop() { return m_Pos.y + m_Size.y * 0.5f; }
	float GetBottom() { return m_Pos.y - m_Size.y * 0.5f; }
	float GetFront() { return m_Pos.z - m_Size.z * 0.5f; }
	float GetBack() { return m_Pos.z + m_Size.z * 0.5f; }

	//HitResultAABB CheckAABB(const BoxCollision* other) const;

private:
	VECTOR* m_TargetPos;
	VECTOR m_LocalPos;
	VECTOR m_Size;
};

