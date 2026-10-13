#pragma once
#include "DxLib.h"
#include <vector>
#include <list>
#include <string>
#include <memory>

class GameObject;

class InputManager
{
public:
	InputManager();
	~InputManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new InputManager;
		}
	}

	static InputManager* GetInstance() { return m_Instance; }

	static void DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

	std::shared_ptr<GameObject> CreateUIInput();

private:
	static InputManager* m_Instance;
	
};