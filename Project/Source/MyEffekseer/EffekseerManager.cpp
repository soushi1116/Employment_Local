#include "DxLib.h"
#include "EffekseerForDXLib.h"
#include "EffekseerManager.h"
#include "EffekseerEffect.h"
#include "EffekseerParameter.h"

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
		"Data/Effect/SkillEffect.efkefc"
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

EffekseerEffect* EffekseerManager::PlayEffect(int type, VECTOR pos)
{
	for (EffekseerEffect* effect : m_Effects)
	{
		if (!effect->IsActive())
		{
			effect->SetActive(true);

			effect->Play(m_EffectHandles[type]);

			effect->SetPos(pos);

			return effect;
		}
	}

	EffekseerEffect* effect = new EffekseerEffect;

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
