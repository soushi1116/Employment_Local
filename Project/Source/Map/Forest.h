#pragma once
#include "DxLib.h"
#include "MapBase.h"

class Forest : public MapBase
{
public:
	Forest();
	~Forest();

public:
	void Init() override;
	void Load() override;
};

