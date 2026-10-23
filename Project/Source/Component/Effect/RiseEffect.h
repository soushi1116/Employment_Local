#pragma once
#include "DxLib.h"
#include "EffectBase.h"

class GameObject;

class RiseEffect : public EffectBase
{
public:
	RiseEffect(GameObject* owner);
	~RiseEffect();

public:
	void Step() override;

};

