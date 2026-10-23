#include "GameObject.h"

GameObject::GameObject()
{
	m_Pos = MyMath::VecZero();
	m_Scale = MyMath::VecZero();
	m_Active = true;
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
	std::shared_ptr<Physics3D> physics = GetComponent<Physics3D>();

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