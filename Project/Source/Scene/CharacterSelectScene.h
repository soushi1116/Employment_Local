#pragma once
#include "SceneBase.h"
#include "../Managers/CharacterManager/CharacterManager.h"

class UIButton;

class CharacterSelectScene : public SceneBase
{
public:
	CharacterSelectScene();
	~CharacterSelectScene();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;

private:
	bool m_IsBoss;
	int m_SelectedNum;
	int m_MaxNum;
};