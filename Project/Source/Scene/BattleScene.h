#pragma once
#include "SceneBase.h"

class BattleScene : public SceneBase
{
public:
	BattleScene();
	~BattleScene();

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