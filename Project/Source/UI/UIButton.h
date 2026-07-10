#pragma once
#include "DxLib.h"
#include "UIParameter.h"
#include "UIBase.h"
#include "../MyMath/MyMath.h"

class UIButton : public UIBase
{
public:
	UIButton();
	~UIButton();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Draw() override;

	void SetIndex(MyMath::VECTOR_INT index) { m_Index = index; }
	MyMath::VECTOR_INT GetIndex() { return m_Index; }
	void SetSelect(bool isSelected) { m_IsSelected = isSelected; }

	bool IsSelected() { return m_IsSelected; }

protected:
	bool m_IsSelected;
	MyMath::VECTOR_INT m_Index;
};