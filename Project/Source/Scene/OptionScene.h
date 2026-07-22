#pragma once
#include "SceneBase.h"
#include "DxLib.h"

enum OptionModeType
{
	SOUND,
	MANUAL,
	MODE_TYPE_MAX,
	MODE_TYPE_NONE = -1
};

class OptionScene : public SceneBase
{
public:
	OptionScene();
	~OptionScene();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;

	void BGMSet();
	void SESet();
	void SetVolumePos();

private:
	VECTOR m_BGMVolumePos;
	VECTOR m_SEVolumePos;

	int m_BGMVolumeHandle;
	int m_SEVolumeHandle;
	int m_ManualHandle;

	bool m_IsBGMSetMode;
	bool m_IsSESetMode;

	OptionModeType m_ModeType;
};