#include "DxLib.h"
#include "Sound.h"

Sound::Sound()
{
	for (int i = 0; i < BGM_TYPE_MAX; i++)
	{
		m_BGMHandle[i] = 0;
	}
	for (int i = 0; i < SE_TYPE_MAX; i++)
	{
		m_SEHandle[i] = 0;
	}

	m_BGMVolume = 0;
	m_SEVolume = 0;
}

Sound::~Sound()
{
	FinBGM();
	FinSE();
}

void Sound::LoadBGM()
{
	//m_BGMHandle[BGM_TITLE]
	m_BGMVolume = 100;
}

void Sound::PlayBGM(BGMType type)
{
	PlaySoundMem(m_BGMHandle[type], DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(m_BGMVolume, m_BGMHandle[type]);
}

void Sound::StopBGM(BGMType type)
{
	StopSoundMem(m_BGMHandle[type]);
}

void Sound::FinBGM()
{
	for (int i = 0; i < BGM_TYPE_MAX; i++)
	{
		DeleteSoundMem(m_BGMHandle[i]);
	}
}

void Sound::LoadSE()
{
	m_SEHandle[SE_CURSOR_MOVE] = LoadSoundMem("Data/Sound/SE/CursorMove.mp3");
	m_SEHandle[SE_CURSOR_SELECT] = LoadSoundMem("Data/Sound/SE/CursorSelect.mp3");

	m_SEVolume = 100;
}

void Sound::PlaySE(SEType type)
{
	PlaySoundMem(m_SEHandle[type], DX_PLAYTYPE_BACK);
	ChangeVolumeSoundMem(m_SEVolume, m_SEHandle[type]);
}

void Sound::FinSE()
{
	for (int i = 0; i < SE_TYPE_MAX; i++)
	{
		DeleteSoundMem(m_SEHandle[i]);
	}
}