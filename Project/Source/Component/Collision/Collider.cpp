#include "Collider.h"
#include "DxLib.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "../../MyMath/MyMath.h"

Collider::Collider(GameObject* owner) : Component(owner)
{
	m_Transform = m_Owner->GetComponent<Transform>();
	m_Collision = nullptr;
	m_CompName = "Collider";
}

Collider::~Collider()
{
	if (m_Collision)
	{
		delete m_Collision;
	}
}

void Collider::Start()
{
	m_Transform = m_Owner->GetComponent<Transform>();
}

void  Collider::Update()
{
	
}

void Collider::Draw()
{
	if (!m_Transform) return;

	MyMath::VECTOR_INT pos = MyMath::Vec2DInt((int)m_Transform->GetPos().x, (int)m_Transform->GetPos().y);

	m_Collision->Draw();
}