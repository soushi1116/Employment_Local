#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "EffekseerManager.h"
#include "EffekseerEffect.h"
#include "EffekseerParameter.h"
#include "BotBeamEffect.h"
#include "PlayerSkillEffect.h"
#include "KnightSuperAttackEffect.h"
#include "BeastSuperAttackEffect.h"

EffekseerManager* EffekseerManager::m_Instance = nullptr;

EffekseerManager::EffekseerManager()
{
	m_EffectHandles = {};
	m_Effects = {};
}

EffekseerManager::~EffekseerManager()
{
	Fin();
}

void EffekseerManager::SetUp()
{
	SetUseDirect3DVersion(DX_DIRECT3D_11);
}

bool EffekseerManager::Init()
{
	if (Effekseer_Init(EFFEKSEER_MAX_PARTICLE) == -1)
	{
		return false;
	}

	SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

	return true;
}

void EffekseerManager::Load()
{
	const char* PATH[] =
	{
		"Data/Effect/SkillEffect.efkefc",
		"Data/Effect/BotBeamEffect.efkefc",
		"Data/Effect/KnightSuperAttackEffect.efkefc",
		"Data/Effect/BeastSuperAttackEffect.efkefc"
	};

	for (const char* path : PATH)
	{
		int handle = LoadEffekseerEffect(path);

		m_EffectHandles.push_back(handle);
	}
}

void EffekseerManager::Start()
{
	
}

EffekseerEffect* EffekseerManager::PlayEffect(EffekseerEffectType type, VECTOR pos)
{
	if (type == EFFEKSEER_EFFECT_TYPE_NONE || type == EFFEKSEER_EFFECT_TYPE_MAX)
	{
		return nullptr;
	}

	if (type < 0 || type >= m_EffectHandles.size())
	{
		return nullptr;
	}

	for (EffekseerEffect* effect : m_Effects)
	{
		if (!effect->IsActive() && effect->GetType() == type)
		{
			effect->SetActive(true);

			effect->Play(m_EffectHandles[type]);

			effect->SetPos(pos);

			return effect;
		}
	}

	EffekseerEffect* effect = nullptr;

	switch (type)
	{
	case EFFEKSEER_SKILL:
		effect = new PlayerSkillEffect;
		break;
	case EFFEKSEER_BOT_BEAM:
		effect = new BotBeamEffect;
		break;
	case EFFEKSEER_KNIGHT_SUPER_ATTACK:
		effect = new KnightSuperAttackEffect;
		break;
	case EFFEKSEER_BEAST_SUPER_ATTACK:
		effect = new BeastSuperAttackEffect;
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

	effect->SetPos(pos);

	m_Effects.push_back(effect);

	return effect;
}

void EffekseerManager::Step()
{
	for (EffekseerEffect* effect : m_Effects)
	{
		effect->Step();
	}
}

void EffekseerManager::Update()
{
	Effekseer_Sync3DSetting();

	for (EffekseerEffect* effect : m_Effects)
	{
		effect->Update();
	}

	UpdateEffekseer3D();
}

void EffekseerManager::Draw()
{
	DrawEffekseer3D();
}

void EffekseerManager::Fin()
{
	for (int handle : m_EffectHandles)
	{
		DeleteEffekseerEffect(handle);
	}

	m_EffectHandles.clear();
	m_EffectHandles.shrink_to_fit();

	for (EffekseerEffect* effect : m_Effects)
	{
		delete effect;
	}

	m_Effects.clear();
	m_Effects.shrink_to_fit();

	Effkseer_End();
}
