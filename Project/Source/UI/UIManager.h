#pragma once
#include "DxLib.h"
#include "UIParameter.h"
#include <list>
#include "../MyMath/MyMath.h"

class UIBase;
class UIButton;

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

	void CreateUIImage(UIName name, VECTOR pos);
	void CreateUIButton(UIName name, VECTOR pos, MyMath::VECTOR_INT index);
	void ResetUI();
	void SetTotalButtonIndex(MyMath::VECTOR_INT totalIndex) { m_TotalButtonIndex = totalIndex; }

	UIName GetSelectedName();

	std::list<UIButton*> GetButtonList() { return m_UIButtonList; }

private:
	static UIManager* m_Instance;

	UIBase* m_UI[UI_TYPE_MAX];

	std::list<UIBase*> m_UIList;
	std::list<UIButton*> m_UIButtonList;

	MyMath::VECTOR_INT m_TotalButtonIndex;
	MyMath::VECTOR_INT m_NowButtonIndex;
};