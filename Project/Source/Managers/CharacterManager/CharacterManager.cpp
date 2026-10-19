#include "CharacterManager.h"
//#include "Rooter/Rooter.h"
//#include "State/State.h"
#include "../../MyMath/MyMath.h"
//#include "Functions/BattleSceneUI.h"
#include "../../Component/AllComponents.h"
#include "../../Collision/CollisionManager.h"
#include "../../Scene/SceneManager.h"
#include "../../Camera/CameraManager.h"
#include "../RendererManager/RendererManager.h"

CharacterManager* CharacterManager::m_Instance = nullptr;

CharacterManager::CharacterManager()
{
	m_BossNum = 0;
	m_WinnerIsBoss = 0;

	for (int i = 0; i < CHARACTER_MAX_NUM; i++)
	{
		m_CharacterType[i] = CharacterType::CHARACTER_TYPE_NONE;
	}
}

CharacterManager::~CharacterManager()
{
	Fin();
}

void CharacterManager::Init()
{
	/*int index = 0;
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

	BattleSceneUI::Init();*/
}

void CharacterManager::Load()
{
	/*for (auto& character : m_CharacterList)
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

	BattleSceneUI::Load();*/
}

void CharacterManager::Start()
{
	/*int index = 0;
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
	}*/

}

void CharacterManager::Step()
{
	/*for (auto& character : m_CharacterList)
	{
		if (character->IsActive())
		{
			character->Step();

			const auto& stateList = character->GetStateList();

			for (auto& state : stateList)
			{
				state->Step();
			}
		}
	}

	for (auto& rooter : m_RooterList)
	{
		if (rooter->IsActive())
		{
			rooter->Step();
		}
	}*/
}

void CharacterManager::Update()
{
	/*for (auto& character : m_CharacterList)
	{
		if (character->IsActive())
		{
			character->Update();

			const auto& stateList = character->GetStateList();

			for (auto& state : stateList)
			{
				state->Update();
			}
		}
	}

	for (auto& rooter : m_RooterList)
	{
		if (rooter->IsActive())
		{
			rooter->Update();
		}
	}

	DeleteRooter();*/
}

void CharacterManager::DrawModel()
{
	/*for (auto& character : m_CharacterList)
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

	SetUseLighting(TRUE);*/
}

void CharacterManager::DrawUI()
{
	/*for (auto& character : m_CharacterList)
	{
		if (character->IsActive())
		{
			character->DrawUI();
		}

		const auto& stateList = character->GetStateList();

		int index = 0;

		for (auto& state : stateList)
		{
			state->Draw(index);
			index++;
		}
	}*/
}

void CharacterManager::Fin()
{
	/*for (auto& character : m_CharacterList)
	{
		delete character;
	}

	m_CharacterList.clear();

	for (auto& rooter : m_RooterList)
	{
		delete rooter;
	}

	m_RooterList.clear();*/
}

std::shared_ptr<GameObject> CharacterManager::CreateCharacter(bool isPlayer, bool inBattleScene, CharacterType type)
{
	// GameObject生成
	auto obj = std::make_shared<GameObject>();
	obj->AddTag(TAG_CHARACTER);

	int index = static_cast<int>(m_Characters.size());

	// 3DPhysicsコンポーネント追加
	auto newPhysics = obj->AddComponent<Physics3D>();

	// Collisionコンポーネント追加
	auto collision = std::make_shared<SphereCollision>();
	newPhysics->SetCollision(collision);

	// Inputコンポーネント追加
	auto characterInput = obj->AddComponent<CharacterInput>();

	std::shared_ptr<InputBase> newInput = nullptr;

	std::shared_ptr<GameObject> cameraObj = nullptr;

	if (isPlayer)
	{
		newInput = std::make_shared<PlayerInput>();

		// Cameraコンポーネント追加
		cameraObj = CameraManager::GetInstance()->CreateCamera(PLAYER_CAMERA);
		cameraObj->GetComponent<Camera>()->SetParent(obj);
	}
	else
	{
		newInput = std::make_shared<NPCInput>();
	}

	characterInput->SetInput(newInput);

	auto characterParameter = obj->AddComponent<CharacterParameter>();

	// サイズ等補正
	newPhysics->SetScale(MyMath::VecSame(10.0f));

	newPhysics->SetUseGravity(true);

	newPhysics->SetCollPosOffset(MyMath::VecY(9.0f));
	newPhysics->SetCollScaleOffset(MyMath::VecSame(1.8f));

	auto animator = obj->AddComponent<Animator>();

	std::shared_ptr<CharacterMove> characterMove = nullptr;

	switch (type)
	{
	case CharacterType::KNIGHT:
	{
		auto model = obj->AddComponent<ModelRenderer>("Data/Character/Knight.x");
		model->SetTexure("Data/Character/Knight_diffuse.png");
		obj->SetName("Knight");
		characterMove = obj->AddComponent<Knight>();
		characterParameter->SetType(CharacterType::KNIGHT);
		characterParameter->SetMaxHp(80);
		characterParameter->SetPower(15);
		break;
	}
	case CharacterType::NINJA:
	{
		auto model = obj->AddComponent<ModelRenderer>("Data/Character/Ninja.x");
		model->SetTexure("Data/Character/Ninja_diffuse.png");
		model->SetRotYOffset(DX_PI_F);
		obj->SetName("Ninja");
		characterMove = obj->AddComponent<Ninja>();
		characterParameter->SetType(CharacterType::NINJA);
		characterParameter->SetMaxHp(50);
		characterParameter->SetPower(30);
		newPhysics->SetPos(MyMath::VecZ(-50.0f));
		break;
	}
	case CharacterType::FAIRY:
	{
		auto model = obj->AddComponent<ModelRenderer>("Data/Character/Fairy.x");
		model->SetTexure("Data/Character/Fairy_diffuse.png");
		model->SetRotYOffset(DX_PI_F);
		obj->SetName("Fairy");
		characterMove = obj->AddComponent<Fairy>();
		characterParameter->SetType(CharacterType::FAIRY);
		characterParameter->SetMaxHp(30);
		break;
	}
	case CharacterType::ROBOT:
	{
		auto model = obj->AddComponent<ModelRenderer>("Data/Character/Robot.x");
		obj->SetName("Robot");
		characterMove = obj->AddComponent<Robot>();
		characterParameter->SetType(CharacterType::ROBOT);
		characterParameter->SetMaxHp(300);
		characterParameter->SetPower(10);
		newPhysics->SetPos(MyMath::VecZ(50.0f));
		break;
	}
	case CharacterType::BEAST:
	{
		auto model = obj->AddComponent<ModelRenderer>("Data/Character/Beast.x");
		model->SetTexure("Data/Character/Beast_diffuse.png");
		model->SetRotYOffset(DX_PI_F);
		obj->SetName("Beast");
		characterMove = obj->AddComponent<Beast>();
		characterParameter->SetType(CharacterType::BEAST);
		characterParameter->SetMaxHp(250);
		characterParameter->SetPower(15);
		break;
	}
	default: return nullptr;
	}

	characterParameter->SetHp(characterParameter->GetMaxHp());

	// 攻撃用コリジョン生成
	auto attackCollision = std::make_shared<DamageCollision>();
	attackCollision->SetRadius(10.0f);
	attackCollision->SetParentIndex(index);
	attackCollision->SetDamage(characterParameter->GetPower());
	characterParameter->SetAttackCollision(attackCollision);

	CollisionManager::GetInstance()->AddDamageCollision(attackCollision);

	characterParameter->SetPlayer(isPlayer);
	characterParameter->SetInBattleScene(inBattleScene);
	characterParameter->SetIndex(index);

	auto inputComp = obj->AddComponent<CharacterInput>();

	InputBase* input = nullptr;

	if (isPlayer)
	{
		input = new PlayerInput;
	}
	else
	{
		input = new NPCInput;
	}

	inputComp->SetInput(newInput);

	if (type == CharacterType::ROBOT || type == CharacterType::BEAST)
	{
		characterParameter->SetBoss(true);
	}

	// カメラ生成
	SceneBase* scene = SceneManager::GetInstance()->GetNowScene();
	scene->Instantiate(obj);
	if (isPlayer)
	{
		scene->Instantiate(cameraObj);
	}

	// ステータスUI生成
	if (inBattleScene)
	{
		auto characterUI = RendererManager::GetInstance()->CreateCharacterUI(characterParameter);
		for (auto& ui : characterUI)
		{
			scene->Instantiate(ui);
		}
	}

	m_Characters.push_back(obj);

	return obj;
}

//CharacterBase* CharacterManager::GetCharacter(CharacterType type)
//{
//	/*for (auto character : m_CharacterList)
//	{
//		if (character != nullptr && character->GetType() == type)
//		{
//			return character;
//		}
//	}*/
//	return nullptr;
//}

//void CharacterManager::CreateRooter(CharacterBase* parent, CharacterBase* target)
//{
//	Rooter* rightRooter = new Rooter;
//	rightRooter->Init();
//	rightRooter->SetAvoidRight(true);
//	rightRooter->SetParent(parent);
//	rightRooter->SetTarget(target);
//	rightRooter->Start();
//
//	Rooter* leftRooter = new Rooter;
//	leftRooter->Init();
//	leftRooter->SetAvoidRight(false);
//	leftRooter->SetParent(parent);
//	leftRooter->SetTarget(target);
//	leftRooter->Start();
//
//	rightRooter->SetPair(leftRooter);
//	leftRooter->SetPair(rightRooter);
//
//	m_RooterList.push_back(rightRooter);
//	m_RooterList.push_back(leftRooter);
//}
//
//void CharacterManager::SetInactiveOlder(Rooter* rooter)
//{
//	for (auto& currentRooter : m_RooterList)
//	{
//		if (currentRooter->GetParent() == rooter->GetParent())
//		{
//			currentRooter->SetActive(false);
//		}
//
//		if (currentRooter == rooter) break;
//	}
//}
//
//void CharacterManager::DeleteRooter()
//{
//	m_RooterList.remove_if([](const Rooter* rooter) {
//		if (!rooter) return true;
//
//		if (!rooter->IsActive())
//		{
//			delete rooter;
//
//			return true;
//		}
//		return false;
//		});
//}
//
//void CharacterManager::ClearRooter()
//{
//	for (auto& rooter : m_RooterList)
//	{
//		delete rooter;
//	}
//
//	m_RooterList.clear();
//}