#pragma once
#include "DxLib.h"
#include "UIParameter.h"
#include <vector>
#include <list>
#include "../MyMath/MyMath.h"

class UIBase;
class UIButton;
class UIText;

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
	UIText* CreateUIText(const char* text, VECTOR pos, unsigned int color, int scale);
	void DeleteUI(UIBase* deleteUI);
	void ResetUI();
	void SetTotalButtonIndex(MyMath::VECTOR_INT totalIndex) { m_TotalButtonIndex = totalIndex; }

	void SetXFixed(bool fixed) { m_XFixed = fixed; }
	void SetYFixed(bool fixed) { m_YFixed = fixed; }

	void RandomSelect();

	UIName GetSelectedName();

	std::vector<UIButton*> GetButtonList() { return m_UIButtonList; }
	std::list<UIBase*> GetUIList() { return m_UIList; }
	UIBase* GetUI(UIName name);

private:
	// UIƒ{ƒ^ƒ“‚ÌŒÅ’è
	bool m_XFixed;
	bool m_YFixed;
	bool m_IsCursorMovable;

	CursorState m_CursorState;
	CursorState m_PrevCursorState;

	int m_CursorMoveTimer;

	static UIManager* m_Instance;

	UIBase* m_UI[UI_TYPE_MAX];

	std::list<UIBase*> m_UIList;
	std::vector<UIButton*> m_UIButtonList;

	MyMath::VECTOR_INT m_TotalButtonIndex;
	MyMath::VECTOR_INT m_NowButtonIndex;
};