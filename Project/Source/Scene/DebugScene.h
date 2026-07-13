#pragma once
#include "SceneBase.h"

class Floor;

class DebugScene : public SceneBase
{
public:
	DebugScene();
	~DebugScene();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;

private:
};