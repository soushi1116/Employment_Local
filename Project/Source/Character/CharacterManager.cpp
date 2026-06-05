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
	m_Character[PLAYER] = new Player;
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
		character->Step();
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

CharacterBase* CharacterManager::CreateCharacter(CharacterType type)
{
	CharacterBase* character = m_Character[type]->Clone();

	m_CharacterList.push_back(character);

	return character;
}