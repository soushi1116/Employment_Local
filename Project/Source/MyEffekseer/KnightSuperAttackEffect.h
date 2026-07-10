#pragma once
#include "DxLib.h"
#include "EffekseerEffect.h"

class KnightSuperAttackEffect : public EffekseerEffect
{
public:
	KnightSuperAttackEffect();
	~KnightSuperAttackEffect();

public:
	void Step() override;

};

