#pragma once
#include "../Component.h"
#include <memory>
#include "../../Input/InputParameter.h"

class GameObject;
class InputBase;

class CharacterInput : public Component
{
public:
	CharacterInput(GameObject* owner);
	~CharacterInput() override;

	void Step() override;

	void SetInput(InputBase* input) { m_Input = input; }

	template <typename T>
	T* GetInput()
	{
		return dynamic_cast<T*>(m_Input);
	}

	virtual void InputLeftStickX(int input);
	virtual void InputLeftStickY(int input);
	virtual void InputRightStickX(int input);
	virtual void InputRightStickY(int input);
	virtual void TriggerButton(BattleTrigger trigger);

	virtual int GetInputBattle(BattleInput input);
	virtual bool IsTriggerBattle(BattleTrigger trigger);

private:
	InputBase* m_Input = nullptr;
};
