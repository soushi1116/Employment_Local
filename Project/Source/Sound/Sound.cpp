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
	m_BGMHandle[BGM_TITLE] = LoadSoundMem("Data/Sound/BGM/TitleScene.mp3");
	m_BGMHandle[BGM_HOME] = LoadSoundMem("Data/Sound/BGM/HomeScene.mp3");
	m_BGMHandle[BGM_SELECT] = LoadSoundMem("Data/Sound/BGM/SelectScene.mp3");
	m_BGMHandle[BGM_BATTLE] = LoadSoundMem("Data/Sound/BGM/BattleScene.mp3");
	m_BGMHandle[BGM_RESULT] = LoadSoundMem("Data/Sound/BGM/ResultScene.mp3");
	m_BGMVolume = 100;
}

void Sound::PlayBGM(BGMType type)
{
	if (CheckSoundMem(m_BGMHandle[type]) != 1)
	{
		PlaySoundMem(m_BGMHandle[type], DX_PLAYTYPE_LOOP);
		ChangeVolumeSoundMem(m_BGMVolume, m_BGMHandle[type]);
	}
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

bool Sound::CheckBGMPlaying(BGMType type)
{
	if (CheckSoundMem(m_BGMHandle[type]) == 1)
	{
		return true;
	}
	return false;
}

void Sound::LoadSE()
{
	m_SEHandle[SE_GAME_START] = LoadSoundMem("Data/Sound/SE/Operation/GameStart.mp3");
	m_SEHandle[SE_CURSOR_MOVE] = LoadSoundMem("Data/Sound/SE/Operation/CursorMove.mp3");
	m_SEHandle[SE_CURSOR_SELECT] = LoadSoundMem("Data/Sound/SE/Operation/CursorSelect.mp3");
	m_SEHandle[SE_MISSION_SELECT] = LoadSoundMem("Data/Sound/SE/Operation/MissionSelect.mp3");
	m_SEHandle[SE_CANCEL] = LoadSoundMem("Data/Sound/SE/Operation/Cancel.mp3");

	m_SEHandle[SE_KNIGHT_ATTACK] = LoadSoundMem("Data/Sound/SE/Knight/KnightAttack.mp3");
	m_SEHandle[SE_KNIGHT_SKILL] = LoadSoundMem("Data/Sound/SE/Knight/KnightSkill.mp3");
	m_SEHandle[SE_KNIGHT_SUPER_ATTACK] = LoadSoundMem("Data/Sound/SE/Knight/KnightSuperAttack.mp3");

	m_SEHandle[SE_BOT_ATTACK] = LoadSoundMem("Data/Sound/SE/Bot/BotAttack.mp3");
	m_SEHandle[SE_BOT_SKILL] = LoadSoundMem("Data/Sound/SE/Bot/BotSkill.mp3");
	m_SEHandle[SE_BOT_SUPER_ATTACK] = LoadSoundMem("Data/Sound/SE/Bot/BotSuperAttack.mp3");

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