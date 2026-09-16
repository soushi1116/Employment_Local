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

	void UIButtonScroll(VECTOR delta);

	void RandomSelect();

	void SetActive(bool active) { m_Active = active; }

	UIName GetSelectedName();

	ButtonGroupType GetType() { return m_Type; }

	std::vector<UIButton*> GetUIList() { return m_UIButtonList; }

private:
	bool m_Active;

	bool m_IsResetIndex; // 非アクティブ→アクティブになった時インデックスをリセットするか

	ButtonGroupType m_Type;

	MyMath::VECTOR_INT m_TotalButtonIndex;
	MyMath::VECTOR_INT m_NowButtonIndex;

	MyMath::VECTOR_INT m_ScrollIndexMin; // この範囲を超えたらスクロール開始
	MyMath::VECTOR_INT m_ScrollIndexMax; // この範囲を超えたらスクロール終了

	VECTOR m_ScrollDelta;

	// UIボタンの固定
	bool m_XFixed;
	bool m_YFixed;
	bool m_IsCursorMovable;

	CursorState m_CursorState;
	CursorState m_PrevCursorState;

	int m_CursorMoveTimer;
	std::vector<UIButton*> m_UIButtonList;

	UIButton* m_UIButton[UI_BUTTON_MAX_NUM];
};

