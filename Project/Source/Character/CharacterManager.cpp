#include "CharacterManager.h"
#include "Player.h"
#include "Enemy.h"
#include "../MyMath/MyMath.h"

CharacterManager* CharacterManager::m_Instance = nullptr;

CharacterManager::CharacterManager()
{
	m_ParentNum = 0;

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
	CreateCharacter(PLAYER);

	for (int i = 0; i < CHARACTER_MAX_NUM; i++)
	{
		CreateCharacter(ENEMY);
	}

	int index = 0;
	for (auto& character : m_CharacterList)
	{
		character->Init();

		if (index == m_ParentNum)
		{
			character->SetParent();
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
		character->SetPosAndIndex(index, m_ParentNum);
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
		character->SetColor();
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

void CharacterManager::CreateCharacter(CharacterType type)
{
	switch (type)
	{
	case PLAYER:
	{
		Player* newPlayer = new Player;

		m_CharacterList.push_back(newPlayer);

	}
	break;
	case ENEMY:
	{
		Enemy* newEnemy = new Enemy;

		m_CharacterList.push_back(newEnemy);
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
				if (attacker->IsParent() != opponent->IsParent())
				{
					if (attacker->GetAttackHitFlag())
					{
						opponent->Damage(attacker);
						attacker->AttackHitFlagFalse();
					}
				}
			}
		}
	}
	
	
}