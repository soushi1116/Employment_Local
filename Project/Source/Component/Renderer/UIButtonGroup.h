#pragma once
#include "../Component.h"
#include <memory>
#include <vector>
#include "../../MyMath/MyMath.h"

class GameObject;
class UIButton;
class UIInput;
class Timer;

enum ButtonGroupName
{
	GROUP_NAME_HOME,

	GROUP_NAME_OPTION,
	GROUP_NAME_SOUND,
	
	GROUP_NAME_BOSS_SELECT,

	GROUP_NAME_CHARACTER_SELECT_CHALLENGER,
	GROUP_NAME_CHARACTER_SELECT_BOSS,

	GROUP_NAME_RESULT,

	GROUP_NAME_MAX,
	GROUP_NAME_NONE = -1
};

class UIButtonGroup : public Component
{
public:
	UIButtonGroup(GameObject* owner);
	~UIButtonGroup();

	void Start() override;
	void Update() override;

public:
	void AddUIButton(UIButton* button) { m_UIButtons.push_back(button); }
	void SetGroupName(ButtonGroupName name) { m_GroupName = name; }
	void SetActive(bool active) { m_Active = active; }

	void SetTotalIndex(MyMath::VECTOR_INT index) { m_TotalIndex = index; }
	MyMath::VECTOR_INT GetCurrentIndex() const { return m_CurrentIndex; }

	void CheckCursor(std::shared_ptr<UIInput> input);

	bool IsActive() { return m_Active; }
	ButtonGroupName GetGroupName() { return m_GroupName; }

	void SetInactiveInvisible(bool invisible) { m_InactiveInvisible = invisible; }
	bool IsInactiveInvisible() const { return m_InactiveInvisible; }

	void SetCursorTimer(std::weak_ptr<Timer> timer) { m_CursorTimer = timer; }

private:
	bool m_Active;
	bool m_InactiveInvisible; // 非アクティブ時に　true:描画しない　false:暗く描画

	MyMath::VECTOR_INT m_TotalIndex;
	MyMath::VECTOR_INT m_CurrentIndex;

	std::vector<UIButton*> m_UIButtons;
	ButtonGroupName m_GroupName;

	std::weak_ptr<Timer> m_CursorTimer;

};
