#pragma once
#include "MissionBase.h"

class KillBaster : public MissionBase
{
public:
	KillBaster();
	~KillBaster();

	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
};
