#pragma once
#include "DxLib.h"
#include "Component.h"
#include "ComponentParameter.h"
#include <vector>
#include <memory>
#include <utility>
#include <string>

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	void Start();
	void Update();
	void Draw();
	void ApplyPushBack();

	template <typename T, typename... Args>
	std::shared_ptr<T> AddComponent(Args&&... args)
	{
		auto component = std::make_shared<T>(this, std::forward<Args>(args)...);
		m_Components.push_back(component);
		return component;
	}

	template <typename T>
	std::shared_ptr<T> GetComponent()
	{
		for (auto& component : m_Components)
		{
			if (auto casted = std::dynamic_pointer_cast<T>(component))
			{
				return casted;
			}
		}
		return nullptr;
	}

	void SetName(std::string name) { m_ObjName = name; }
	void AddTag(Tag tag) { m_Tags.push_back(tag); }
	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetScale(VECTOR scale) { m_Scale = scale; }

	std::string GetName() { return m_ObjName; }
	bool CompareTag(Tag tag)
	{
		for (auto thisTag : m_Tags)
		{
			if (thisTag == tag) return true;
		}
		return false;
	}
	VECTOR GetPos() { return m_Pos; }
	VECTOR GetScale() { return m_Scale; }

private:
	std::vector<std::shared_ptr<Component>> m_Components;
	std::string m_ObjName;
	std::vector<Tag> m_Tags;

	// Å¶3DPhysicsÇ∆èdï°ÇµÇƒÇ¢ÇÈÇÃÇ≈óvâ¸ëP
	VECTOR m_Pos;
	VECTOR m_Scale;
};

#include "AllComponents.h"