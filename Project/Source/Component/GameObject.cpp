#include "GameObject.h"

GameObject::GameObject()
{
	m_Pos = MyMath::VecZero();
	m_Scale = MyMath::VecZero();
}

GameObject::~GameObject()
{

}

void GameObject::Start()
{
	for (auto& component : m_Components)
	{
		component->Start();
	}
}

void GameObject::Update()
{
	for (auto& component : m_Components)
	{
		component->Step();
	}

	for (auto& component : m_Components)
	{
		component->Update();
	}
}

void GameObject::ApplyPushBack()
{
	std::shared_ptr<_3DPhysics> physics = GetComponent< _3DPhysics>();

	if (physics != nullptr)
	{
		physics->CollisionPushBack();
	}
}

void GameObject::Draw()
{
	for (auto& component : m_Components)
	{
		component->Draw();
	}
}