#pragma once
#include "DxLib.h"
#include "MapBase.h"

class Factory : public MapBase
{
public:
	Factory();
	~Factory();

public:
	void Init() override;
	void Load() override;
};

