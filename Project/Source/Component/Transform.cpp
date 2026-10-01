#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

Transform::Transform(GameObject* owner) : Component(owner)
{
	m_Pos = MyMath::VecZero();
	m_Rot = MyMath::VecZero();
	m_Scale = MyMath::VecSame(1.0f);
}