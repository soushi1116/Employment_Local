#pragma once
#include "DxLib.h"
#include "UIParameter.h"
#include <list>

class UIBase;

class UIManager
{
public:
	UIManager();
	~UIManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new UIManager;
		}
	}

	static UIManager* GetInstance() { return m_Instance; }

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

	void CreateUI(UIType type, VECTOR pos);
	void ResetUI();

private:
	static UIManager* m_Instance;

	UIBase* m_UI[UI_TYPE_MAX];

	std::list<UIBase*> m_UIList;
};

