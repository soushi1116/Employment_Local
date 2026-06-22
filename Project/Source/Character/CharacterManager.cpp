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
		character->Start();
		character->SetPosAndIndex(index, m_ParentNum);

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
	Player* player = nullptr;

	for (auto character : m_CharacterList)
	{
		if (character->GetType() == PLAYER)
		{
			player = static_cast<Player*>(character);
			break;
		}
	}
	
	if (!player) return;

	if (player->GetActionType() != ACTION_ATTACK
		&& player->GetActionType() != ACTION_SUPER_ATTACK)
	{
		return;
	}

	int playerHandle = player->GetHandle();

	MV1RefreshCollInfo(playerHandle, -1);

	int swordFrameIndex = MV1SearchFrame(player->GetHandle(), "円柱");

	VECTOR swordPos = MV1GetFramePosition(playerHandle, swordFrameIndex);
	float swordRadius = 7.0f;

	for (auto character : m_CharacterList)
	{
		if (character->GetType() != ENEMY) continue;

		Enemy* enemy = static_cast<Enemy*>(character);

		VECTOR enemyPos = enemy->GetPos();
		float enemyRadius = enemy->GetRadius();

		MV1_COLL_RESULT_POLY_DIM Hitresult = MV1CollCheck_Sphere(playerHandle, -1, enemyPos, enemyRadius);

		if (Hitresult.HitNum > 0 && player->GetAttackHitFlag())
		{
			enemy->Damage(player);
			player->AttackHitFlagFalse();
		}
	}
}