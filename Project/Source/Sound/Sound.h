#pragma once
#include "DxLib.h"

enum BGMType
{
	BGM_TITLE,
	BGM_TYPE_MAX,
	BGM_TYPE_NONE = -1
};

enum SEType
{
	SE_CURSOR_MOVE,
	SE_CURSOR_SELECT,
	SE_TYPE_MAX,
	SE_TYPE_NONE = -1
};

class Sound
{
public:
	Sound();
	~Sound();

public:
	void LoadBGM();
	void PlayBGM(BGMType type);
	void StopBGM(BGMType type);
	void FinBGM();

public:
	void LoadSE();
	void PlaySE(SEType type);
	void FinSE();

private:
	int m_BGMHandle[BGM_TYPE_MAX] = { 0 };
	int m_SEHandle[SE_TYPE_MAX] = { 0 };

	int m_BGMVolume;
	int m_SEVolume;
};