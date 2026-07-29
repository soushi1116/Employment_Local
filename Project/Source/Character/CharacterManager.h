#pragma once
#include "CharacterBase.h"
#include "CharacterParameter.h"
#include <vector>

const int CHARACTER_MAX_NUM = 4;

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
	void DrawModel();
	void DrawUI();
	void Fin();

public:
	void CheckSwordCollision();

public:
	void CreateCharacter(bool isPlayer, CharacterType type);
	CharacterBase* GetCharacter(CharacterType type);
	std::vector<CharacterBase*> GetCharacterList() { return m_CharacterList; }
	bool WinnerIsBoss() { return m_WinnerIsBoss; }
	void SetBossNum(int num) { m_BossNum = num; }
	void SetWinnerBoss(bool win)
	{
		m_WinnerIsBoss = win;
	}
	CharacterBase* SearchPlayer()
	{
		for (auto character : m_CharacterList)
		{
			if (character->IsPlayer())
			{
				return character;
			}
		}

		return nullptr;
	}
	CharacterBase* SearchBoss()
	{
		for (auto character : m_CharacterList)
		{
			if (character->IsBoss())
			{
				return character;
			}
		}

		return nullptr;
	}
	int GetBossNum() { return m_BossNum; }

	CharacterType GetCharacterType(int characterNum) { return m_CharacterType[characterNum]; }

	void SetCharacterType(int characterNum, CharacterType type) { m_CharacterType[characterNum] = type; }

private:
	static CharacterManager* m_Instance;

	CharacterBase* m_Character[CHARACTER_TYPE_MAX];

	std::vector<CharacterBase*> m_CharacterList;

	int m_BossNum;

	bool m_WinnerIsBoss;

	CharacterType m_CharacterType[CHARACTER_MAX_NUM];
};
