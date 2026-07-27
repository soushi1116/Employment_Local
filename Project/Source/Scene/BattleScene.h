#pragma once
#include "SceneBase.h"

class Floor;
class SkyDome;

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
	int m_SkillGaugeHandle;
	int m_SuperAttackGaugeHandle;
	int m_BattleFinishCount;

	bool m_BattleFinished;

	SkyDome* m_SkyDome;
};