#pragma once
#include "DxLib.h"
#include "EffekseerEffect.h"

class PlayerSkillEffect : public EffekseerEffect
{
public:
	PlayerSkillEffect();
	~PlayerSkillEffect();

public:
	void Step() override;

};

