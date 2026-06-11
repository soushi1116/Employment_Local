#include "Player.h"
#include "CharacterParameter.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../MyEffekseer/EffekseerManager.h"
#include "../MyEffekseer/EffekseerParameter.h"

const float PLAYER_ROTATION_SPEED = 0.1f;
const float PLAYER_MOVE_SPEED = 0.1f;
const float PLAYER_GRAVITY = 0.01f;

const float PLAYER_SUPER_ATTACK_MOVE_SPEED = 0.5f;

const float PLAYER_WIDTH = 4.0f;
const float PLAYER_HEIGHT = 11.2f;
const float PLAYER_DEPTH = 2.0f;

const float ANIMATION_SPEED = 1.0f;

Player::Player() : CharacterBase()
{
	m_AnimationAttachIndex = 0;
	m_AnimationTotalTime = 0.0f;
	m_AnimationNowTime = 0.0f;
	m_IsLoopAnimation = false;
	m_ActionType = PLAYER_ACTION_NONE;
	m_NowAnimation = PLAYER_ANIMATION_STOP;
}

Player::~Player()
{
	Fin();
}

void Player::Init()
{

}

void Player::Load()
{
	m_Handle = MV1LoadModel("Data/Character/Player.x");
}

void Player::Start()
{
	m_Scale = VGet(1.0f, 1.0f, 1.0f);

	m_Active = true;

	m_Type = PLAYER;

	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, -0.7f, 0.0f));
	m_AABB->SetSize(VGet(PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_DEPTH));

	PlayAnimation(PLAYER_ANIMATION_STOP, true);
}

void Player::Step()
{
	m_Move = VGet(0.0f, 0.0f, 0.0f);

	if (m_ActionType == PLAYER_ACTION_NONE)
	{
		/*if (Input::IsInputKey(Input::KEY_LEFT))
		{
			m_Move.x = -PLAYER_MOVE_SPEED;
		}
		if (Input::IsInputKey(Input::KEY_RIGHT))
		{
			m_Move.x = PLAYER_MOVE_SPEED;
		}
		if (Input::IsInputKey(Input::KEY_UP))
		{
			m_Move.z = PLAYER_MOVE_SPEED;
		}
		if (Input::IsInputKey(Input::KEY_DOWN))
		{
			m_Move.z = -PLAYER_MOVE_SPEED;
		}*/

		/*if (Input::GetLeftStickX() > 0)
		{
			m_Move.x = PLAYER_MOVE_SPEED;
		}
		if (Input::GetLeftStickX() < 0)
		{
			m_Move.x = -PLAYER_MOVE_SPEED;
		}
		if (Input::GetLeftStickY() > 0)
		{
			m_Move.z = -PLAYER_MOVE_SPEED;
		}
		if (Input::GetLeftStickY() < 0)
		{
			m_Move.z = PLAYER_MOVE_SPEED;
		}*/

		m_Move.x = PLAYER_MOVE_SPEED * Input::GetLeftStickX() / 1000;
		m_Move.z = -PLAYER_MOVE_SPEED * Input::GetLeftStickY() / 1000;

		if (m_Move.x == 0.0f && m_Move.z == 0.0f)
		{
			PlayAnimation(PLAYER_ANIMATION_STOP, true);
		}
		else
		{
			PlayAnimation(PLAYER_ANIMATION_WALK, true);
		}
	}

	if (Input::IsTriggerButton(Input::BUTTON_RB))
	{
		if (m_ActionType != PLAYER_ACTION_NONE) return;

		PlayAnimation(PLAYER_ANIMATION_ATTACK, false);
		m_ActionType = PLAYER_ACTION_ATTACK;
	}

	if (Input::IsTriggerButton(Input::BUTTON_B))
	{
		if (m_ActionType != PLAYER_ACTION_NONE) return;

		PlayAnimation(PLAYER_ANIMATION_SKILL, false);
		m_ActionType = PLAYER_ACTION_SKILL;

		VECTOR playerFootPos = VGet(m_Pos.x, m_Pos.y - PLAYER_HEIGHT / 2, m_Pos.z);

		EffekseerManager::GetInstance()->PlayEffect(EFFEKSEER_SKILL, playerFootPos);
	}

	if (Input::IsTriggerButton(Input::BUTTON_LB))
	{
		if (m_ActionType != PLAYER_ACTION_NONE) return;

		PlayAnimation(PLAYER_ANIMATION_SUPER_ATTACK, false);

		m_ActionType = PLAYER_ACTION_SUPER_ATTACK;
	}

	if (m_ActionType == PLAYER_ACTION_SUPER_ATTACK)
	{
		m_Move.z = PLAYER_SUPER_ATTACK_MOVE_SPEED;
	}

	/*if (Input::IsInputKey(Input::KEY_LEFT))
	{
		m_Rot.y -= PLAYER_ROTATION_SPEED;
	}
	if (Input::IsInputKey(Input::KEY_RIGHT))
	{
		m_Rot.y += PLAYER_ROTATION_SPEED;
	}*/

	/*if (m_Rot.y < 0.0f)
	{
		m_Rot.y += DX_TWO_PI_F;
	}
	else if (m_Rot.y > DX_TWO_PI_F)
	{
		m_Rot.y -= DX_TWO_PI_F;
	}*/

	/*if (Input::IsInputKey(Input::KEY_UP))
	{
		VECTOR front = MyMath::VecForwardZX(m_Rot.y);

		m_Move = MyMath::VecScale(front, PLAYER_MOVE_SPEED);
	}*/

	m_Move.y = m_Gravity;

	if (!m_Randing) m_Gravity -= PLAYER_GRAVITY;

	UpdateAnimation();
}

void Player::PlayAnimation(PlayerAnimationType anim, bool isLoop)
{
	if (anim == m_NowAnimation) return;

	MV1DetachAnim(m_Handle, m_AnimationAttachIndex);

	m_AnimationAttachIndex = MV1AttachAnim(m_Handle, anim);

	m_AnimationTotalTime = MV1GetAttachAnimTotalTime(m_Handle, m_AnimationAttachIndex);

	m_AnimationNowTime = 0.0f;

	m_IsLoopAnimation = isLoop;

	m_NowAnimation = anim;
}

void Player::UpdateAnimation()
{
	MV1SetAttachAnimTime(m_Handle, m_AnimationAttachIndex, m_AnimationNowTime);

	m_AnimationNowTime += ANIMATION_SPEED;

	if (m_AnimationNowTime > m_AnimationTotalTime)
	{
		if (m_IsLoopAnimation)
		{
			m_AnimationNowTime = 0.0f;
		}
		else
		{
			m_AnimationNowTime = m_AnimationTotalTime;
			if (m_ActionType != PLAYER_ACTION_NONE)
			{
				m_ActionType = PLAYER_ACTION_NONE;
			}
		}
	}
}