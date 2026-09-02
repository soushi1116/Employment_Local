#pragma once
#include "DxLib.h"
#include "MapBase.h"

class TestMap : public MapBase
{
public:
	TestMap();
	~TestMap();

public:
	void Init() override;
	void Load() override;
};

