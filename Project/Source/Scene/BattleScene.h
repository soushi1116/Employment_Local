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
	int m_BattleFinishCount;

	SkyDome* m_SkyDome;

	// 対戦結果用テキスト
	std::shared_ptr<GameObject> m_ResultText;
};