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
		newRobot->Load();
		newRobot->SetBoss();

		m_CharacterList.push_back(newRobot);
		break;
	}
	case BEAST:
	{
		Beast* newBeast = new Beast;

		newBeast->Init();
		newBeast->SetPlayer(isPlayer);
		newBeast->Load();
		newBeast->SetBoss();

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

			if (attacker == nullptr || opponent == nullptr) {
				printf("Error: attacker または opponent が nullptr です。\n");
				return; // 処理を中断
			}

			// 2. ハンドルの有効性チェック（例: ハンドルが -1 など不正な値でないか）
			// ※お使いのフレームワークの仕様に合わせて調整してください
			if (attackerHandle < 0) {
				printf("Error: attackerHandle が無効です (%d)\n", attackerHandle);
				return; // 処理を中断
			}

			// 3. 安全を確認してから当たり判定を実行
			MV1_COLL_RESULT_POLY_DIM Hitresult = MV1CollCheck_Sphere(attackerHandle, -1, opponentPos, opponentRadius);

			// 4. 結果のチェック
			printf("Hitresult.HitNum: %d\n", Hitresult.HitNum);

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