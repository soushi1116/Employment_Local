#pragma once
#include "Sound.h"
#include <memory>
#include "../Component/AllComponents.h"
#include "../MyEnums/MyEnums.h"

class Sound;

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new SoundManager;
		}
	}

	static SoundManager* GetInstance() { return m_Instance; }

	static void DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

public:
	void Fin();

public:
	void CreateSound();
	Sound* GetSound() { return m_Sound; }

	void PlayCharacterSE(CharacterType characterType, CharacterAction actionType);

private:
	static SoundManager* m_Instance;

	Sound* m_Sound;
};

