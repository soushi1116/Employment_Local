#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "EffectManager.h"
#include "../../Component/AllComponents.h"
#include "../../Component/Component.h"
#include "../../Component/GameObject.h"
#include "../../Scene/SceneManager.h"

EffectManager* EffectManager::m_Instance = nullptr;

EffectManager::EffectManager()
{
	m_EffectHandles = {};
	m_Effects = {};
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
		"Data/Effect/PoisonEffect.efkefc",
		"Data/Effect/PowerUpStateEffect.efkefc",
		"Data/Effect/DefenceUpStateEffect.efkefc",
		"Data/Effect/BoostStateEffect.efkefc",
		"Data/Effect/PoisonStateEffect.efkefc"
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
	std::shared_ptr<EffectBase> effect = nullptr;

	switch (type)
	{
	case EFFEKSEER_BOT_BEAM:
		break;
	case EFFEKSEER_BEAST_SUPER_ATTACK:
		break;
	case EFFEKSEER_HP_HEAL:
		effect = effectObj->AddComponent<RiseEffect>();
		break;
	case EFFEKSEER_POWER_UP:
		effect = effectObj->AddComponent<RiseEffect>();
		break;
	case EFFEKSEER_DEFENCE_UP:
		effect = effectObj->AddComponent<RiseEffect>();
		break;
	case EFFEKSEER_BOOST:
		effect = effectObj->AddComponent<RiseEffect>();
		break;
	case EFFEKSEER_POISON:
		effect = effectObj->AddComponent<RiseEffect>();
		break;
	case EFFEKSEER_POWER_UP_STATE:
		effect = effectObj->AddComponent<RiseEffect>();
		break;
	case EFFEKSEER_DEFENCE_UP_STATE:
		effect = effectObj->AddComponent<RiseEffect>();
		break;
	case EFFEKSEER_BOOST_STATE:
		effect = effectObj->AddComponent<RiseEffect>();
		break;
	case EFFEKSEER_POISON_STATE:
		effect = effectObj->AddComponent<RiseEffect>();
		break;
	case EFFEKSEER_EFFECT_TYPE_MAX:
		break;
	case EFFEKSEER_EFFECT_TYPE_NONE:
		break;
	default:
		break;
	}

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

	
}

void EffectManager::Draw()
{
	
}

void EffectManager::Fin()
{

}
