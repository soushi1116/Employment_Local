#pragma once
#include "DxLib.h"
#include "SoundParameter.h"

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

	bool CheckBGMPlaying(BGMType type);

public:
	void LoadSE();
	void PlaySE(SEType type);
	void FinSE();

public:
	void SetBGMVolume(int volume);
	void SetSEVolume(int volume);

	int GetBGMVolume() { return m_BGMVolume; }
	int GetSEVolume() { return m_SEVolume; }

private:
	int m_BGMHandle[BGM_TYPE_MAX] = { 0 };
	int m_SEHandle[SE_TYPE_MAX] = { 0 };

	int m_BGMVolume;
	int m_SEVolume;
};