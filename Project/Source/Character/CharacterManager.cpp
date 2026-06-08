#include "CharacterManager.h"
#include "Player.h"

CharacterManager* CharacterManager::m_Instance = nullptr;

CharacterManager::CharacterManager()
{
	for (int i = 0; i < CHARACTER_TYPE_MAX; i++)
	{
		m_Character[i] = nullptr;
	}
}

CharacterManager::~CharacterManager()
{
	Fin();
}

void CharacterManager::Init()
{
	for (int i = 0; i < CHARACTER_TYPE_MAX; i++)
	{
		m_Character[i]->Init();
	}
}

void CharacterManager::Load()
{
	for (int i = 0; i < CHARACTER_TYPE_MAX; i++)
	{
		m_Character[i]->Load();
	}
}

void CharacterManager::Start()
{
	for (int i = 0; i < CHARACTER_TYPE_MAX; i++)
	{
		CreateCharacter(PLAYER);
	}

	for (auto character : m_CharacterList)
	{
		character->Start();
	}
}

void CharacterManager::Step()
{
	for (auto character : m_CharacterList)
	{
		character->Step();
	}
}

void CharacterManager::Update()
{
	for (auto character : m_CharacterList)
	{
		character->Update();
	}
}

void CharacterManager::Draw()
{
	for (auto character : m_CharacterList)
	{
		character->Draw();
	}
}

void CharacterManager::Fin()
{
	for (auto character : m_CharacterList)
	{
		delete character;
	}

	m_CharacterList.clear();

	for (auto character : m_Character)
	{
		delete character;
	}
}

void CharacterManager::CreateCharacter(CharacterType type)
{
	switch (type)
	{
	case PLAYER:
		if (m_Character[PLAYER] == nullptr)
		{
			m_Character[PLAYER] = new Player;

			m_CharacterList.push_back(m_Character[PLAYER]);
		}
		break;
	case CHARACTER_TYPE_MAX:
		break;
	case CHARACTER_TYPE_NONE:
		break;
	default:
		break;
	}
}