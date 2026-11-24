#include "CharacterManager.h"
#include "../../MyMath/MyMath.h"
#include "../../Component/AllComponents.h"
#include "../CollisionManager/CollisionManager.h"
#include "../../Scene/SceneManager.h"
#include "../CameraManager/CameraManager.h"
#include "../RendererManager/RendererManager.h"
#include "../BattleManager/BattleManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>

CharacterManager* CharacterManager::m_Instance = nullptr;

const VECTOR BOSS_SPAWN_POS = VGet(0.0f, 0.0f, -150.0f);
const VECTOR CHALLENGER_SPAWN_POS = VGet(0.0f, 0.0f, 150.0f);

const std::string STATUS_DATA_PATH = "Data/Parameters/CharacterStatus.csv";

CharacterManager::CharacterManager()
	:m_BossNum(0)
	, m_BossCreated(0)
	, m_PlayerType(CHARACTER_TYPE_NONE)
	, m_BossType(CHARACTER_TYPE_NONE)
{

}

CharacterManager::~CharacterManager()
{
	
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
	auto collision = obj->AddComponent<SphereCollision>();
	newPhysics->SetCollision(collision);

	// Inputコンポーネント追加
	auto characterInput = obj->AddComponent<CharacterInput>();

	std::shared_ptr<InputBase> newInput;

	std::shared_ptr<GameObject> cameraObj = nullptr;

	if (isPlayer)
	{
		auto playerInput = obj->AddComponent<PlayerInput>();
		newInput = playerInput;

		// Cameraコンポーネント追加
		cameraObj = CameraManager::GetInstance()->CreateCamera(PLAYER_CAMERA);
		cameraObj->GetComponent<Camera>()->SetParent(obj);
	}
	else
	{
		auto characterAI = obj->AddComponent<CharacterAI>();

		auto npcInput = obj->AddComponent<NPCInput>();
		newInput = npcInput;
	}

	characterInput->SetInput(newInput);

	std::shared_ptr<CharacterParameter> characterParameter = obj->AddComponent<CharacterParameter>();

	newPhysics->SetUseGravity(true);

	newPhysics->SetCollPosOffset(MyMath::VecY(9.0f));
	newPhysics->SetCollScaleOffset(MyMath::VecSame(1.8f));

	auto animator = obj->AddComponent<Animator>();

	// 攻撃用コリジョン生成
	auto attackCollision = obj->AddComponent<DamageCollision>();
	auto superAttackCollision = obj->AddComponent<DamageCollision>();

	std::shared_ptr<CharacterMove> characterMove = nullptr;

	std::vector<float> statusData = LoadStatusData(STATUS_DATA_PATH, type);

	switch (type)
	{
	case CharacterType::KNIGHT:
	{
		auto model = obj->AddComponent<ModelRenderer>("Data/Character/Knight.x");
		model->SetTexure("Data/Character/Knight_diffuse.png");
		obj->SetName("Knight");
		characterMove = obj->AddComponent<Knight>();

		break;
	}
	case CharacterType::NINJA:
	{
		auto model = obj->AddComponent<ModelRenderer>("Data/Character/Ninja.x");
		model->SetTexure("Data/Character/Ninja_diffuse.png");
		model->SetRotYOffset(DX_PI_F);
		obj->SetName("Ninja");
		characterMove = obj->AddComponent<Ninja>();
		break;
	}
	case CharacterType::FAIRY:
	{
		auto model = obj->AddComponent<ModelRenderer>("Data/Character/Fairy.x");
		model->SetTexure("Data/Character/Fairy_diffuse.png");
		model->SetRotYOffset(DX_PI_F);
		obj->SetName("Fairy");
		characterMove = obj->AddComponent<Fairy>();
		break;
	}
	case CharacterType::ROBOT:
	{
		auto model = obj->AddComponent<ModelRenderer>("Data/Character/Robot.x");
		obj->SetName("Robot");
		characterMove = obj->AddComponent<Robot>();
		break;
	}
	case CharacterType::BEAST:
	{
		auto model = obj->AddComponent<ModelRenderer>("Data/Character/Beast.x");
		model->SetTexure("Data/Character/Beast_diffuse.png");
		model->SetRotYOffset(DX_PI_F);
		obj->SetName("Beast");
		characterMove = obj->AddComponent<Beast>();
		superAttackCollision->SetRadius(20.0f);
		superAttackCollision->SetParentIndex(index);
		superAttackCollision->SetDamage(characterParameter->GetPower());
		break;
	}
	default: return nullptr;
	}

	if (!isPlayer)
	{
		characterParameter->SetBoss(true);
	}

	characterParameter->SetType(type);

	if (!statusData.empty()) characterParameter->SetStatus(statusData);

	characterParameter->SetHp(characterParameter->GetMaxHp());

	VECTOR spawnPos = MyMath::VecZero();

	characterParameter->SetPlayer(isPlayer);
	characterParameter->SetInBattleScene(inBattleScene);
	characterParameter->SetIndex(index);

	if (characterParameter->IsBoss())
	{
		spawnPos = BOSS_SPAWN_POS;

		newPhysics->SetScale(MyMath::VecSame(10.0f));
	}
	else
	{
		spawnPos = CHALLENGER_SPAWN_POS;

		newPhysics->SetScale(MyMath::VecSame(10.0f));

		if (characterParameter->IsPlayer())
		{
			newPhysics->SetAngleY(DX_PI_F);
			newPhysics->SetRot(VGet(0.0f, DX_PI_F, 0.0f));
		}
	}

	newPhysics->SetPos(spawnPos);
	characterParameter->SetStartPos(spawnPos);

	attackCollision->SetRadius(10.0f);
	attackCollision->SetParentIndex(index);
	attackCollision->SetDamage(characterParameter->GetPower());

	auto inputComp = obj->AddComponent<CharacterInput>();

	std::weak_ptr<InputBase> input;

	if (isPlayer)
	{
		auto playerInput = obj->AddComponent<PlayerInput>();
		input = playerInput;
	}
	else
	{
		auto npcInput = obj->AddComponent<NPCInput>();
		input = npcInput;
	}

	inputComp->SetInput(newInput);

	attackCollision->SetIsBoss(characterParameter->IsBoss());

	characterParameter->SetAttackCollision(attackCollision);

	CollisionManager::GetInstance()->AddDamageCollision(attackCollision);

	characterParameter->SetSuperAttackCollision(superAttackCollision);

	CollisionManager::GetInstance()->AddDamageCollision(superAttackCollision);

	SceneBase* scene = SceneManager::GetInstance()->GetNowScene();
	scene->Instantiate(obj);

	// カメラ生成
	if (isPlayer)
	{
		scene->Instantiate(cameraObj);
	}

	// ステータスUI生成
	if (inBattleScene)
	{
		auto characterUI = RendererManager::GetInstance()->CreateCharacterBattleUI(characterParameter);
		for (auto& ui : characterUI)
		{
			scene->Instantiate(ui);
		}
	}

	m_Characters.push_back(obj);

	if (characterParameter->IsBoss()) m_BossCreated = true;

	return obj;
}

bool CharacterManager::IsBossAlive()
{
	for (auto& characterObj : m_Characters)
	{
		if (auto characterPtr = characterObj.lock())
		{
			std::shared_ptr<CharacterParameter> characterParam = characterPtr->GetComponent<CharacterParameter>();

			if (characterParam->IsBoss())
			{
				if (characterParam->GetAction() != CharacterAction::ACTION_DIE)
				{
					return true;
				}
			}
		}
	}
	return false;
}

/// <summary>
/// ステータスデータの読み取り
/// </summary>
/// <param name="filePath">ファイル名</param>
/// <returns>読み取りできたかどうか</returns>
std::vector<float> CharacterManager::LoadStatusData(const std::string& filePath, CharacterType type)
{
	std::vector<float> statusData;

	int typeIndex = static_cast<int>(type);

	std::ifstream file(filePath);
	if (!file.is_open()) return statusData;

	std::string line;
	bool isFirstLine = true;

	int rowIndex = 0;

	while (std::getline(file, line))
	{
		if (line.empty()) continue;

		// 1行目は無視
		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		if (rowIndex != typeIndex)
		{
			rowIndex++;
			continue;
		}

		std::stringstream ss(line);
		std::string value;

		int columnIndex = 0;

		while (std::getline(ss, value, ','))
		{
			float currentStatusData = 0.0f;

			value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());

			// 1列目は無視
			if (columnIndex == 0)
			{
				columnIndex++;
				continue;
			}

			if (!value.empty())
			{
				try
				{
					currentStatusData = std::stof(value);
				}
				catch (const std::invalid_argument&)
				{
					currentStatusData = 0.0f;
				}
				catch (const std::out_of_range&)
				{
					currentStatusData = 0.0f;
				}
			}

			statusData.push_back(currentStatusData);
			columnIndex++;
		}
		break;
	}
	return statusData;
}