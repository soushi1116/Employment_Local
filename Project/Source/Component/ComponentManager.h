#pragma once
#include "Component.h"
#include <list>
#include <vector>

class ComponentManager
{
public:
	ComponentManager();
	~ComponentManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new ComponentManager;
		}
	}

	static ComponentManager* GetInstance() { return m_Instance; }

	static void DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

public:
	void CreateComponent();


private:
	static ComponentManager* m_Instance;
};

