#include "CharacterManager.h"
#include "Knight.h"
#include "Ninja.h"
#include "Robot.h"
#include "../MyMath/MyMath.h"

CharacterManager* CharacterManager::m_Instance = nullptr;

CharacterManager::CharacterManager()
{
	m_BossNum = 0;
	m_WinnerIsBoss = 0;

	m_PlayerCharacter = CHARACTER_TYPE_NONE;

	for (int i = 0; i < CPU_CHARACTER_MAX_NUM; i++)
	{
		m_CPUCharacter[i] = CHARACTER_TYPE_NONE;
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
}

void CharacterManager::Start()
{
	int index = 0;
	for (auto& character : m_CharacterList)
	{
		character->SetPosAndIndex(index, m_BossNum);
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

	CheckSwordCollision();
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
	// NINJAにいかない
	switch (type)
	{
	case KNIGHT:
	{
		Knight* newKnight = new Knight;

		newKnight->Init();
		newKnight->Load();
		newKnight->SetPlayer(isPlayer);

		m_CharacterList.push_back(newKnight);
		break;
	}
	case NINJA:
	{
		Ninja* newNinja = new Ninja;

		newNinja->Init();
		newNinja->Load();
		newNinja->SetPlayer(isPlayer);

		m_CharacterList.push_back(newNinja);
		break;
	}
	case ROBOT:
	{
		Robot* newRobot = new Robot;

		newRobot->Init();
		newRobot->Load();
		newRobot->SetPlayer(isPlayer);
		newRobot->SetBoss();

		m_CharacterList.push_back(newRobot);
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

void CharacterManager::CheckSwordCollision()
{
	for (auto attacker : m_CharacterList)
	{		
		if (attacker->GetActionType() != ACTION_ATTACK
			&& attacker->GetActionType() != ACTION_SUPER_ATTACK)
		{
			continue;
		}

		int attackerHandle = attacker->GetHandle();

		MV1RefreshCollInfo(attackerHandle, -1);

		int swordFrameIndex = MV1SearchFrame(attacker->GetHandle(), "円柱");

		VECTOR swordPos = MV1GetFramePosition(attackerHandle, swordFrameIndex);
		float swordRadius = 7.0f;

		for (auto opponent : m_CharacterList)
		{
			if (opponent == attacker) continue;

			VECTOR opponentPos = opponent->GetPos();
			float opponentRadius = opponent->GetRadius();

			MV1_COLL_RESULT_POLY_DIM Hitresult = MV1CollCheck_Sphere(attackerHandle, -1, opponentPos, opponentRadius);

			if (Hitresult.HitNum > 0 && attacker->GetAttackHitFlag())
			{
				if (attacker->IsBoss() != opponent->IsBoss())
				{
					if (attacker->GetAttackHitFlag())
					{
						opponent->Damage(attacker, attacker->GetPower());
						attacker->AttackHitFlagFalse();
					}
				}
			}
		}
	}
	
	
}