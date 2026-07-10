#pragma once
#include "DxLib.h"
#include "EffekseerEffect.h"

class BotBeamEffect : public EffekseerEffect
{
public:
	BotBeamEffect();
	~BotBeamEffect();

public:
	void Step() override;

};

