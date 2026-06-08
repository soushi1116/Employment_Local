#pragma once
#include "CharacterBase.h"
#include "CharacterParameter.h"
#include <list>

class CharacterManager
{
public:
	CharacterManager();
	~CharacterManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new CharacterManager;
		}
	}

	static CharacterManager* GetInstance() { return m_Instance; }

	static void DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

public:
	void CreateCharacter(CharacterType type);
	CharacterBase* GetCharacter(CharacterType type) { return m_Character[type]; }

private:
	static CharacterManager* m_Instance;

	CharacterBase* m_Character[CHARACTER_TYPE_MAX];

	std::list<CharacterBase*> m_CharacterList;
};
