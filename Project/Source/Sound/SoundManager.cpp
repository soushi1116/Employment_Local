#include "DxLib.h"
#include "SoundManager.h"
#include "Sound.h"

SoundManager* SoundManager::m_Instance = nullptr;

SoundManager::SoundManager()
	:m_Sound(nullptr)
{
	
}

SoundManager::~SoundManager()
{
	Fin();
}

void SoundManager::CreateSound()
{
	if (!m_Sound)
	{
		m_Sound = new Sound;
	}
}

void SoundManager::Fin()
{
	if (m_Sound)
	{
		delete m_Sound;
		m_Sound = nullptr;
	}
}

void SoundManager::PlayCharacterSE(CharacterType characterType, CharacterAction actionType)
{
	auto sound = SoundManager::GetInstance()->GetSound();

	switch (characterType)
	{
	case KNIGHT:
		if (actionType == ACTION_ATTACK) sound->PlaySE(SE_KNIGHT_ATTACK);
		if (actionType == ACTION_SKILL) sound->PlaySE(SE_POWER_UP);
		if (actionType == ACTION_SUPER_ATTACK) sound->PlaySE(SE_KNIGHT_SUPER_ATTACK);
		break;
	case NINJA:
		if (actionType == ACTION_ATTACK) sound->PlaySE(SE_NINJA_ATTACK);
		if (actionType == ACTION_SKILL) sound->PlaySE(SE_NINJA_SKILL);
		if (actionType == ACTION_SUPER_ATTACK) sound->PlaySE(SE_THROW);
		break;
	case FAIRY:
		if (actionType == ACTION_ATTACK) sound->PlaySE(SE_THROW);
		if (actionType == ACTION_SKILL) sound->PlaySE(SE_HP_HEAL);
		if (actionType == ACTION_SUPER_ATTACK) sound->PlaySE(SE_THROW);
		break;
	case ROBOT:
		if (actionType == ACTION_ATTACK) sound->PlaySE(SE_ROBOT_ATTACK);
		if (actionType == ACTION_SKILL) sound->PlaySE(SE_HP_HEAL);
		if (actionType == ACTION_SUPER_ATTACK) sound->PlaySE(SE_ROBOT_SUPER_ATTACK);
		break;
	case BEAST:
		if (actionType == ACTION_ATTACK) sound->PlaySE(SE_BEAST_ATTACK);
		if (actionType == ACTION_SKILL) sound->PlaySE(SE_POWER_UP);
		if (actionType == ACTION_SUPER_ATTACK) sound->PlaySE(SE_BEAST_SUPER_ATTACK);
		break;
	case CHARACTER_TYPE_MAX:
		break;
	case CHARACTER_TYPE_NONE:
		break;
	default:
		break;
	}
}