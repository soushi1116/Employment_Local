#include "DxLib.h"
#include "SoundManager.h"
#include "Sound.h"

SoundManager* SoundManager::m_Instance = nullptr;

SoundManager::SoundManager()
{
	m_Sound = nullptr;
}

SoundManager::~SoundManager()
{
	Fin();
}

void SoundManager::CreateSound()
{
	if (!m_Sound)
	{
		m_Sound = new Sound;
	}
}

void SoundManager::Fin()
{
	if (m_Sound)
	{
		delete m_Sound;
		m_Sound = nullptr;
	}
}