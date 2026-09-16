#pragma once
#include "DxLib.h"
#include "UIParameter.h"
#include <vector>
#include <list>
#include "../MyMath/MyMath.h"

class UIBase;
class UIButton;
class UIText;
class ButtonGroup;

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
	UIButton* CreateUIButton(UIName name, VECTOR pos, MyMath::VECTOR_INT index);
	UIText* CreateUIText(const char* text, VECTOR pos, unsigned int color, int scale);
	ButtonGroup* CreateUIButtonGroup(ButtonGroupType type);
	void DeleteUI(UIBase* deleteUI);
	void ResetUI();	

	void SetPos(VECTOR pos);

	std::list<UIBase*> GetUIList() { return m_UIList; }
	UIBase* GetUI(UIName name);

	UIName GetSelectedName(ButtonGroupType type);

	void SetXFixed(bool fixed, ButtonGroupType type);
	void SetYFixed(bool fixed, ButtonGroupType type);

	void RandomSelect(ButtonGroupType type);

	void SetGroupActive(bool active, ButtonGroupType type);

	ButtonGroup* GetButtonGroup(ButtonGroupType type);

private:
	static UIManager* m_Instance;

	UIBase* m_UI[UI_TYPE_MAX];

	std::list<UIBase*> m_UIList;

	std::list<ButtonGroup*> m_ButtonGroupList;
};