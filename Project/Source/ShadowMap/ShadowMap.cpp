#include "DxLib.h"
#include "ShadowMap.h"
#include "../Managers/CharacterManager/CharacterManager.h"

const int  SHADOW_MAP_SIZE_X = 1024;
const int  SHADOW_MAP_SIZE_Y = 1024;
const VECTOR  SHADOW_MAP_AREA_MIN = VGet(-50.0f, 0.0f, -50.0f);
const VECTOR  SHADOW_MAP_AREA_MAX = VGet(50.0f, 1.0f, 50.0f);

ShadowMap* ShadowMap::m_Instance = nullptr;

ShadowMap::ShadowMap()
{
	m_Handle = 0;
}

ShadowMap::~ShadowMap()
{
	Fin();
}

void ShadowMap::Init()
{
	m_Handle = MakeShadowMap(SHADOW_MAP_SIZE_X, SHADOW_MAP_SIZE_Y);

	VECTOR lightDirection = GetLightDirection();

	SetShadowMapLightDirection(m_Handle, lightDirection);

	SetShadowMapDrawArea(m_Handle, SHADOW_MAP_AREA_MIN, SHADOW_MAP_AREA_MAX);
}

void ShadowMap::Fin()
{
	DeleteShadowMap(m_Handle);
}

void ShadowMap::StartDrawShadowMap()
{
	ShadowMap_DrawSetup(m_Handle);
}

void ShadowMap::EndDrawShadowMap()
{
	ShadowMap_DrawEnd();
}

void ShadowMap::StartAppearsShadowMap()
{
	SetUseShadowMap(0, m_Handle);
}

void ShadowMap::EndAppearsShadowMap()
{
	SetUseShadowMap(0, -1);
}