#pragma once
#include "DxLib.h"
#include <vector>
#include <list>
#include <string>
#include <memory>

class GameObject;

class RendererManager
{
public:
	RendererManager();
	~RendererManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new RendererManager;
		}
	}

	static RendererManager* GetInstance() { return m_Instance; }

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

	std::shared_ptr<GameObject> CreateBackGround(const char* filePath);

private:
	static RendererManager* m_Instance;
};