#include "CharacterManager.h"
#include "Player/Knight.h"
#include "Player/Ninja.h"
#include "Player/Fairy.h"
#include "Boss/Robot.h"
#include "Boss/Beast.h"
#include "../MyMath/MyMath.h"

CharacterManager* CharacterManager::m_Instance = nullptr;

CharacterManager::CharacterManager()
{
	m_BossNum = 0;
	m_WinnerIsBoss = 0;

	for (int i = 0; i < CHARACTER_MAX_NUM; i++)
	{
		m_CharacterType[i] = CHARACTER_TYPE_NONE;
	}

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
	int index = 0;
	for (auto& character : m_CharacterList)
	{
		character->Init();

		if (index == m_BossNum)
		{
			character->SetBoss();
		}

		index++;
	}
}

void CharacterManager::Load()
{
	for (auto& character : m_CharacterList)
	{
		character->Load();
	}

	int stateIcon = 0;
	for (int i = 0; i < STATE_TYPE_MAX; i++)
	{
		switch (i)
		{
		case 0:
			stateIcon = LoadGraph("Data/UI/battleScene/PowerUpIcon.png");
			break;
		case 1:
			stateIcon = LoadGraph("Data/UI/battleScene/DefenceUpIcon.png");
			break;
		case 2:
			stateIcon = LoadGraph("Data/UI/battleScene/PoisonIcon.png");
			break;
		default:
			break;
		}
		m_StateIconList.push_back(stateIcon);
	}
}

void CharacterManager::Start()
{
	int index = 0;
	for (auto& character : m_CharacterList)
	{
		character->SetPosAndIndex(index, m_BossNum);
		switch (index)
		{
		case 0:
			character->SetName("Player");
			break;
		case 1:
			character->SetName("CPU1");
			break;
		case 2:
			character->SetName("CPU2");
			break;
		case 3:
			character->SetName("CPU3");
			break;
		default:
			break;
		}
		character->Start();

		index++;
	}
}

void CharacterManager::Step()
{
	for (auto& character : m_CharacterList)
	{
		character->Step();
	}

	//CheckSwordCollision();
}

void CharacterManager::Update()
{
	for (auto& character : m_CharacterList)
	{
		character->Update();
	}	
}

void CharacterManager::DrawModel()
{
	for (auto& character : m_CharacterList)
	{
		//character->SetColor();
		character->DrawModel();
	}

	SetUseLighting(TRUE);
}

void CharacterManager::DrawUI()
{
	for (auto& character : m_CharacterList)
	{
		character->DrawUI();
	}
}

void CharacterManager::Fin()
{
	for (auto& character : m_CharacterList)
	{
		delete character;
	}

	m_CharacterList.clear();

	for (auto character : m_Character)
	{
		delete character;
	}
}

void CharacterManager::CreateCharacter(bool isPlayer, CharacterType type)
{
	switch (type)
	{
	case KNIGHT:
	{
		Knight* newKnight = new Knight;

		newKnight->Init();
		newKnight->SetPlayer(isPlayer);
		newKnight->Load();

		m_CharacterList.push_back(newKnight);
		break;
	}
	case NINJA:
	{
		Ninja* newNinja = new Ninja;

		newNinja->Init();		
		newNinja->SetPlayer(isPlayer);
		newNinja->Load();

		m_CharacterList.push_back(newNinja);
		break;
	}
	case FAIRY:
	{
		Fairy* newFairy = new Fairy;

		newFairy->Init();
		newFairy->SetPlayer(isPlayer);
		newFairy->Load();

		m_CharacterList.push_back(newFairy);
		break;
	}
	case ROBOT:
	{
		Robot* newRobot = new Robot;

		newRobot->Init();
		newRobot->SetPlayer(isPlayer);
		newRobot->SetBoss();
		newRobot->Load();

		m_CharacterList.push_back(newRobot);
		break;
	}
	case BEAST:
	{
		Beast* newBeast = new Beast;

		newBeast->Init();
		newBeast->SetPlayer(isPlayer);
		newBeast->SetBoss();
		newBeast->Load();
		
		m_CharacterList.push_back(newBeast);
		break;
	}
	case CHARACTER_TYPE_MAX:
		break;
	case CHARACTER_TYPE_NONE:
		break;
	default:
		break;
	}
}

CharacterBase* CharacterManager::GetCharacter(CharacterType type)
{
	for (auto character : m_CharacterList)
	{
		if (character != nullptr && character->GetType() == type)
		{
			return character;
		}
	}
	return nullptr;
}
