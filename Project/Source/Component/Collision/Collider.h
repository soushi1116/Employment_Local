#pragma once
#include "../Component.h"
#include <memory>

class GameObject;
class Transform;
class CollisionBase;

class Collider : public Component
{
public:
	Collider(GameObject* owner);

	~Collider();

	void Start();
	void Update();
	void Draw();

	void SetCollision(CollisionBase* collision) { m_Collision = collision; }

	template <typename T>
	T* GetCollison()
	{
		return dynamic_cast<T*>(m_Collision);
	}

	GameObject* GetOwner() { return m_Owner; }

private:
	std::shared_ptr<Transform> m_Transform;
	CollisionBase* m_Collision;
};