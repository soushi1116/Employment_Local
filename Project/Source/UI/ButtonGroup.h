#pragma once
#include "UIParameter.h"
#include "../MyMath/MyMath.h"
#include <vector>

const int UI_BUTTON_MAX_NUM = 6;

class UIButton;

class ButtonGroup
{
public:
	ButtonGroup();
	~ButtonGroup();

public:
	void Init();
	void Start();
	void Step();
	void Update();
	void Fin();

public:
	void SetTotalButtonIndex(MyMath::VECTOR_INT totalIndex) { m_TotalButtonIndex = totalIndex; }

	void SetXFixed(bool fixed) { m_XFixed = fixed; }
	void SetYFixed(bool fixed) { m_YFixed = fixed; }

	void SetType(ButtonGroupType type) { m_Type = type; }

	void UIButtonScroll(VECTOR diff);

	void RandomSelect();

	UIName GetSelectedName();

	ButtonGroupType GetType() { return m_Type; }

private:
	ButtonGroupType m_Type;

	MyMath::VECTOR_INT m_TotalButtonIndex;
	MyMath::VECTOR_INT m_NowButtonIndex;

	MyMath::VECTOR_INT m_ScrollPosMin;
	MyMath::VECTOR_INT m_ScrollPosMax;

	// UIƒ{ƒ^ƒ“‚ÌŒÅ’è
	bool m_XFixed;
	bool m_YFixed;
	bool m_IsCursorMovable;

	CursorState m_CursorState;
	CursorState m_PrevCursorState;

	int m_CursorMoveTimer;
	std::vector<UIButton*> m_UIButtonList;

	UIButton* m_UIButton[UI_BUTTON_MAX_NUM];
};

