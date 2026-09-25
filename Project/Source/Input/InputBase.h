#pragma once
#include "DxLib.h"
#include "InputParameter.h"

class CharacterBase;

class InputBase
{
public:
	InputBase();
	~InputBase();

	virtual void Init();
	virtual void Start();
	virtual void Step();
	virtual void Update();
	virtual void Fin();

private:
	InputType m_Type;
	BattleInputState m_BattleInput;
	OtherInputState m_OtherInput;
	bool m_InBattleScene;

	CharacterBase* m_ParentCharacter;
};