#include "CollisionBase.h"
#include "../../../MyMath/MyMath.h"

CollisionBase::CollisionBase(GameObject* owner) : Component(owner)
{
	m_Pos = MyMath::VecZero();
	m_PosOffset = MyMath::VecZero();
	m_Size = MyMath::VecSame(1.0f);
}

CollisionBase::~CollisionBase()
{

}