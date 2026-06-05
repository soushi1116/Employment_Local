#pragma once
#include "DxLib.h"
#include "CharacterBase.h"

class Player : public CharacterBase
{
public:
	Player();
	~Player();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

	CharacterBase* Clone() override;

private:

};

