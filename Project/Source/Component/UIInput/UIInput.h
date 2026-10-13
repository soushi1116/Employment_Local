#pragma once
#include "../Component.h"
#include <memory>
#include "../../Input/InputParameter.h"

class GameObject;

class UIInput : public Component
{
public:
	UIInput(GameObject* owner);
	~UIInput() override;

	void Start() override;
	void Step() override;

	virtual bool IsInputUI(UIInputType input) { return m_UIInput == input; }
	virtual bool IsTriggerUI(UITrigger trigger) { return m_UITrigger == trigger; }

private:
	UIInputType m_UIInput = UI_INPUT_NONE;
	UITrigger m_UITrigger = UI_TRIGGER_NONE;


};
