#pragma once
#include "DxLib.h"
#include "CharacterParameter.h"

class CharacterBase
{
public:
	CharacterBase();
	~CharacterBase();

public:
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start() = 0;
	virtual void Step() = 0;

	virtual void Update();
	virtual void Draw();
	virtual void Fin();

	virtual CharacterBase* Clone() = 0;

protected:
	VECTOR m_Pos;
	VECTOR m_Scale;

	bool m_Active;

	int m_Handle;

	CharacterType m_Type;
};