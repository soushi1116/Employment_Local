#include "CharacterManager.h"
#include "Player/Knight.h"
#include "Player/Ninja.h"
#include "Player/Fairy.h"
#include "Boss/Robot.h"
#include "Boss/Beast.h"
#include "Rooter/Rooter.h"
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

	for (auto& rooter : m_RooterList)
	{
		rooter->Init();
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

	for (auto& rooter : m_RooterList)
	{
		rooter->Start();
	}

}

void CharacterManager::Step()
{
	for (auto& character : m_CharacterList)
	{
		if (character->IsActive())
		{
			character->Step();
		}
	}

	for (auto& rooter : m_RooterList)
	{
		if (rooter->IsActive())
		{
			rooter->Step();
		}
	}
}

void CharacterManager::Update()
{
	for (auto& character : m_CharacterList)
	{
		if (character->IsActive())
		{
			character->Update();
		}
	}	

	for (auto& rooter : m_RooterList)
	{
		if (rooter->IsActive())
		{
			rooter->Update();
		}
	}

	DeleteRooter();
}

void CharacterManager::DrawModel()
{
	for (auto& character : m_CharacterList)
	{
		if (character->IsActive())
		{
			character->DrawModel();
		}
	}

	for (auto& rooter : m_RooterList)
	{
		if (rooter->IsActive())
		{
			rooter->Draw();
		}
	}

	SetUseLighting(TRUE);
}

void CharacterManager::DrawUI()
{
	for (auto& character : m_CharacterList)
	{
		if (character->IsActive())
		{
			character->DrawUI();
		}
	}
}

void CharacterManager::Fin()
{
	for (auto& character : m_CharacterList)
	{
		// クローンかどうか
		bool isClone = true;

		// いずれかのベースのキャラクターと一致すればクローンではない
		for (int i = 0; i < CHARACTER_TYPE_MAX; i++)
		{
			if (character == m_Character[i])
			{
				isClone = false;
				break;
			}
		}

		// クローンのみ削除
		if (isClone)
		{
			delete character;
		}
	}

	// ベースのキャラクターを削除
	for (int i = 0; i < CHARACTER_TYPE_MAX; i++)
	{
		if (m_Character[i] != nullptr)
		{
			delete m_Character[i];
			m_Character[i] = nullptr;
		}
	}

	m_CharacterList.clear();

	for (auto& rooter : m_RooterList)
	{
		delete rooter;
	}

	m_RooterList.clear();
}

CharacterBase* CharacterManager::CreateCharacter(bool isPlayer, bool inBattleScene, CharacterType type)
{
	CharacterBase* newCharacter = nullptr;

	switch (type)
	{
	case KNIGHT: newCharacter = new Knight(); break;
	case NINJA: newCharacter = new Ninja(); break;
	case FAIRY: newCharacter = new Fairy(); break;
	case ROBOT: newCharacter = new Robot(); break;
	case BEAST: newCharacter = new Beast(); break;
	default: return nullptr;
	}

	newCharacter->Init();
	newCharacter->SetPlayer(isPlayer);
	newCharacter->ChangeInBattleScene(inBattleScene);

	if (type == ROBOT || type == BEAST)
	{
		newCharacter->SetBoss();
	}

	newCharacter->Load();
	newCharacter->Start();
	m_CharacterList.push_back(newCharacter);

	return newCharacter;
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

void CharacterManager::CreateRooter(CharacterBase* parent, CharacterBase* target)
{
	Rooter* rightRooter = new Rooter;
	rightRooter->Init();
	rightRooter->SetAvoidRight(true);
	rightRooter->SetParent(parent);
	rightRooter->SetTarget(target);
	rightRooter->Start();

	Rooter* leftRooter = new Rooter;
	leftRooter->Init();
	leftRooter->SetAvoidRight(false);
	leftRooter->SetParent(parent);
	leftRooter->SetTarget(target);
	leftRooter->Start();

	rightRooter->SetPair(leftRooter);
	leftRooter->SetPair(rightRooter);

	m_RooterList.push_back(rightRooter);
	m_RooterList.push_back(leftRooter);
}

void CharacterManager::SetInactiveOlder(Rooter* rooter)
{
	for (auto& currentRooter : m_RooterList)
	{
		if (currentRooter->GetParent() == rooter->GetParent())
		{
			currentRooter->SetActive(false);
		}

		if (currentRooter == rooter) break;
	}
}

void CharacterManager::DeleteRooter()
{
	m_RooterList.remove_if([](const Rooter* rooter) {
		if (!rooter) return true;

		if (!rooter->IsActive())
		{
			delete rooter;

			return true;
		}
		return false;
		});
}