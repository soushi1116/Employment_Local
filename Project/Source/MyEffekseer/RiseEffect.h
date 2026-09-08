#pragma once
#include "DxLib.h"
#include "EffekseerEffect.h"

class RiseEffect : public EffekseerEffect
{
public:
	RiseEffect();
	~RiseEffect();

public:
	void Step() override;

};

