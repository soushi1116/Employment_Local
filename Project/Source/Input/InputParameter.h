#pragma once

enum InputType
{
	INPUT_TYPE_PLAYER,
	INPUT_TYPE_NPC,
	INPUT_TYPE_NETWORK,

	INPUT_TYPE_MAX,
	INPUT_TYPE_NONE = -1
};

enum CharacterInputType
{
	PLAYER_INPUT,
	OTHER_1_INPUT,
	OTHER_2_INPUT,
	OTHER_3_INPUT,

	CHARACTER_INPUT_TYPE_MAX,
	CHARACTER_INPUT_TYPE_NONE = -1,
};

// バトルシーン用
struct BattleInputData
{
	int m_LeftStickX;
	int m_LeftStickY;
	int m_RightStickX;
	int m_RightStickY;
};

enum BattleInput
{
	BATTLE_INPUT_NONE = 0,

	INPUT_MOVE_X = 1U << 0,
	INPUT_MOVE_Y = 1U << 1,
	INPUT_ANGLE_ROT_X = 1U << 2,
	INPUT_ANGLE_ROT_Y = 1U << 3,
};

enum BattleTrigger : unsigned int
{
	BATTLE_TRIGGER_NONE = 0,

	TRIGGER_ATTACK = 1U << 0,
	TRIGGER_SKILL = 1U << 1,
	TRIGGER_SUPER_ATTACK = 1U << 2,
};

// バトルシーン以外用
enum OtherInput : unsigned int
{
	OTHER_INPUT_NONE = 0,

	INPUT_CURSOR_UP = 1U << 0,
	INPUT_CURSOR_DOWN = 1U << 1,
	INPUT_CURSOR_RIGHT = 1U << 2,
	INPUT_CURSOR_LEFT = 1U << 3,
};

enum  OtherTrigger : unsigned int
{
	OTHER_TRIGGER_NONE = 0,
	
	INPUT_SELECT = 1U << 0,
	INPUT_CANCEL = 1U << 1,
};