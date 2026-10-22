#pragma once
#include "../Component.h"
#include "DxLib.h"
#include "../../MyMath/MyMath.h"
#include <memory>

class GameObject;
class SpriteRenderer;
class UIButtonGroup;

class UIButton : public Component
{
public:
	UIButton(GameObject* owner);
	~UIButton();

	void Start() override;
	void Update() override;

public:
	MyMath::VECTOR_INT GetIndex() const { return m_Index; }
	bool IsSelected() const { return m_IsSelected; }

	void SetIndex(MyMath::VECTOR_INT index) { m_Index = index; }
	void SetIsSelected(bool isSelected) { m_IsSelected = isSelected; }

	void SetParent(std::weak_ptr<UIButtonGroup> parent);

private:
	MyMath::VECTOR_INT m_Index;
	bool m_IsSelected;
	std::weak_ptr<SpriteRenderer> m_SpriteRenderer;
	std::weak_ptr<UIButtonGroup> m_ParentGroup;
};
