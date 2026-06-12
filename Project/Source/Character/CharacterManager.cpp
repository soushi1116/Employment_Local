#include "CharacterManager.h"
#include "Player.h"
#include "Enemy.h"

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
		CreateCharacter(ENEMY);
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

	CheckSwordCollision();
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

	Player* realPlayer = nullptr;
	for (auto character : m_CharacterList)
	{
		// リストの中から「Playerクラス」のものを探す
		if (Player* p = dynamic_cast<Player*>(character))
		{
			realPlayer = p;
			break; // 見つかったらループを抜ける
		}
	}

	// 画面最前面に描画するための設定
	SetUseZBuffer3D(FALSE);
	SetWriteZBuffer3D(FALSE);

	if (realPlayer != nullptr)
	{
		int handle = realPlayer->GetHandle();

		// ハンドルの値そのものと、検索結果を両方表示する
		DrawFormatString(10, 10, GetColor(255, 0, 0), "Player Model Handle: %d", handle);

		if (handle > 0) // ハンドルが正常な場合のみフレーム検索
		{
			int swordIndex = MV1SearchFrame(handle, "円柱");
			DrawFormatString(10, 30, GetColor(255, 0, 0), "SwordIndex: %d", swordIndex);
		}
		else
		{
			DrawFormatString(10, 30, GetColor(255, 0, 0), "SwordIndex: Cannot search (Handle error)");
		}
	}
	else
	{
		DrawFormatString(10, 10, GetColor(255, 0, 0), "Player Instance NOT FOUND in List!");
	}

	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

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

			m_Character[PLAYER]->Load();
			m_Character[PLAYER]->Start();

			m_CharacterList.push_back(m_Character[PLAYER]);
		}
		break;

	case ENEMY:
		if (m_Character[ENEMY] == nullptr)
		{
			m_Character[ENEMY] = new Enemy;

			m_Character[ENEMY]->Load();
			m_Character[ENEMY]->Start();

			m_CharacterList.push_back(m_Character[ENEMY]);
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

void CharacterManager::CheckSwordCollision()
{
	Player* player = nullptr;
	Enemy* enemy = nullptr;

	for (auto character : m_CharacterList)
	{
		if (Player* p = dynamic_cast<Player*>(character)) player = p;
		if (Enemy* e = dynamic_cast<Enemy*>(character)) enemy = e;
	}
	
	if (player == nullptr || enemy == nullptr) return;

	if (player->GetActionType() != PLAYER_ACTION_ATTACK
		&& player->GetActionType() != PLAYER_ACTION_SUPER_ATTACK)
	{
		return;
	}

	int playerHandle = player->GetHandle();
	int swordFrameIndex = MV1SearchFrame(player->GetHandle(), "円柱");

	VECTOR enemyPos = enemy->GetPos();
	float enemyRadius = enemy->GetRadius();

	MV1_COLL_RESULT_POLY_DIM Hitresult = MV1CollCheck_Sphere(playerHandle, -1, enemyPos, enemyRadius);

	if (Hitresult.HitNum > 0)
	{
		enemy->Damage();
	}
}