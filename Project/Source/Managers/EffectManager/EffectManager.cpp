#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "EffectManager.h"
#include "../../Component/AllComponents.h"
#include "../../Component/Component.h"
#include "../../Component/GameObject.h"
#include "../../Scene/SceneManager.h"

EffectManager* EffectManager::m_Instance = nullptr;

EffectManager::EffectManager()
	: m_EffectHandles({})
	, m_Effects({})
{
	
}

EffectManager::~EffectManager()
{
	Fin();
}

void EffectManager::SetUp()
{
	SetUseDirect3DVersion(DX_DIRECT3D_11);
}

bool EffectManager::Init()
{
	if (Effekseer_Init(EFFEKSEER_MAX_PARTICLE) == -1)
	{
		return false;
	}

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	return true;
}

void EffectManager::Load()
{
	const char* PATH[] =
	{
		"Data/Effect/SkillEffect.efkefc",
		"Data/Effect/BotBeamEffect.efkefc",
		"Data/Effect/BeastSuperAttackEffect.efkefc",
		"Data/Effect/HealEffect.efkefc",
		"Data/Effect/PowerUpEffect.efkefc",
		"Data/Effect/DefenceUpEffect.efkefc",
		"Data/Effect/BoostEffect.efkefc",
		"Data/Effect/SpeedUpEffect.efkefc",
		"Data/Effect/PoisonEffect.efkefc",
		"Data/Effect/PowerUpStateEffect.efkefc",
		"Data/Effect/DefenceUpStateEffect.efkefc",
		"Data/Effect/BoostStateEffect.efkefc",
		"Data/Effect/PoisonStateEffect.efkefc",
		"Data/Effect/DamageEffect.efkefc"
	};

	for (const char* path : PATH)
	{
		int handle = LoadEffekseerEffect(path);

		m_EffectHandles.push_back(handle);
	}
}

void EffectManager::Start()
{

}

std::shared_ptr<GameObject> EffectManager::PlayEffect(EffekseerEffectType type, std::weak_ptr<Physics3D> parentPhysics)
{
	if (type == EFFEKSEER_EFFECT_TYPE_NONE || type == EFFEKSEER_EFFECT_TYPE_MAX)
	{
		return nullptr;
	}

	if (type < 0 || type >= m_EffectHandles.size())
	{
		return nullptr;
	}

	auto effectObj = std::make_shared<GameObject>();

	auto effectPhysics = effectObj->AddComponent<Physics3D>();
	std::shared_ptr<EffectBase> effect = effectObj->AddComponent<EffectBase>();

	effect->SetActive(true);

	effect->Play(m_EffectHandles[type]);

	auto physicsPtr = parentPhysics.lock();
	effect->SetPos(physicsPtr->GetPos());
	effect->SetParentPhysics(parentPhysics);

	m_Effects.push_back(effectObj);

	SceneBase* nowScene = SceneManager::GetInstance()->GetNowScene();
	nowScene->Instantiate(effectObj);

	return effectObj;
}

void EffectManager::Step()
{
	
}

void EffectManager::Update()
{

	DeleteEffect();
}

void EffectManager::Draw()
{
	
}

void EffectManager::Fin()
{

}

void EffectManager::DeleteEffect()
{
	if (m_Effects.empty()) return;

	SceneBase* nowScene = SceneManager::GetInstance()->GetNowScene();

	std::vector<std::shared_ptr<GameObject>> deleteTargets;

	m_Effects.erase(
		std::remove_if(m_Effects.begin(), m_Effects.end(),
			[&deleteTargets](const auto& effect)
			{
				auto effectPtr = effect.lock();

				if (!effectPtr) return true;

				std::shared_ptr <EffectBase> effectCmp = effectPtr->GetComponent<EffectBase>();

				if (!effectCmp) return true;

				if (!effectCmp->IsActive())
				{
					deleteTargets.push_back(effectPtr);
					return true;
				}

				return false;
			}),
		m_Effects.end()
	);

	for (const auto& target : deleteTargets)
	{
		nowScene->Delete(target);
	}
}