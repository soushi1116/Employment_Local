#pragma once
#include "DxLib.h"
#include "EffekseerEffect.h"

class BeastSuperAttackEffect : public EffekseerEffect
{
public:
	BeastSuperAttackEffect();
	~BeastSuperAttackEffect();

public:
	void Step() override;

};

