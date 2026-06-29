#pragma once
#include "CharacterBase.h"
#include "CharacterParameter.h"
#include <list>

const int CHARACTER_MAX_NUM = 3;

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
	void CreateCharacter(CharacterType type);
	CharacterBase* GetCharacter(CharacterType type);
	std::list<CharacterBase*> GetCharacterList() { return m_CharacterList; }
	bool WinnerIsParent() { return m_WinnerIsParent; }
	void SetParentNum(int num) { m_ParentNum = num; }
	void SetWinnerParent(bool win)
	{
		m_WinnerIsParent = win;
	}

private:
	static CharacterManager* m_Instance;

	CharacterBase* m_Character[CHARACTER_TYPE_MAX];

	std::list<CharacterBase*> m_CharacterList;

	int m_ParentNum;

	bool m_WinnerIsParent;
};
