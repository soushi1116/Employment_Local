#include "Player.h"
#include "CharacterParameter.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../MyEffekseer/EffekseerManager.h"
#include "../MyEffekseer/EffekseerParameter.h"
#include "../Camera/CameraManager.h"
#include "../Camera/CameraBase.h"

const float PLAYER_ROTATION_SPEED = 0.03f;
const float PLAYER_MOVE_SPEED = 0.3f;
const float PLAYER_GRAVITY = 0.01f;

const float PLAYER_SUPER_ATTACK_MOVE_SPEED = 0.5f;

const VECTOR PLAYER_SIZE = VGet(4.0f, 11.2f, 4.0f);
const VECTOR PLAYER_DEFAULT_POS = VGet(0.0f, 0.0f, -10.0f);

const VECTOR SWORD_POS_OFFSET = VGet(2.0f, 3.0f, 4.0f);
const VECTOR SWORD_COLLISION_SIZE = VGet(1.0f, 10.0f, 6.0f);

const float ANIMATION_SPEED = 1.0f;

const int PLAYER_HP_MAX = 100;
const int PLAYER_DEFAULT_POWER = 10;

Player::Player() : CharacterBase()
{
	m_MaxHp = PLAYER_HP_MAX;
	m_DefaultPos = PLAYER_DEFAULT_POS;

	m_AnimationAttachIndex = 0;
	m_AnimationTotalTime = 0.0f;
	m_AnimationNowTime = 0.0f;
	m_IsLoopAnimation = false;
	m_NowAnimation = PLAYER_ANIMATION_STOP;

	m_AnimTotalTimes[PLAYER_ANIMATION_STOP] = 10.0f;
	m_AnimTotalTimes[PLAYER_ANIMATION_WALK] = 70.0f;
	m_AnimTotalTimes[PLAYER_ANIMATION_ATTACK] = 30.0f;
	m_AnimTotalTimes[PLAYER_ANIMATION_SKILL] = 30.0f;
	m_AnimTotalTimes[PLAYER_ANIMATION_SUPER_ATTACK] = 50.0f;
	m_AnimTotalTimes[PLAYER_ANIMATION_DIE] = 180.0f;
	m_AnimTotalTimes[PLAYER_ANIMATION_DAMAGED] = 30.0f;
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

	MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
}

void Player::Start()
{
	m_Scale = VGet(1.0f, 1.0f, 1.0f);
	m_Pos = m_DefaultPos;

	m_Active = true;

	m_Speed = PLAYER_MOVE_SPEED;
	m_Hp = m_MaxHp;
	m_Power = PLAYER_DEFAULT_POWER;

	m_Type = PLAYER;

	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 5.5f, 0.0f));
	m_AABB->SetSize(PLAYER_SIZE);

	m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(VGet(0.0f, 5.5f, 0.0f));
	m_Sphere->SetRadius(PLAYER_SIZE.y / 2.0f);

	PlayAnimation(PLAYER_ANIMATION_STOP, true);
}

void Player::Step()
{
	m_Move = VGet(0.0f, 0.0f, 0.0f);

	if (m_ActionType != ACTION_SUPER_ATTACK
		&& m_ActionType != ACTION_ATTACK)
	{
		m_AttackHitFlag = false;
	}

	if (m_ActionType == ACTION_TYPE_NONE)
	{
		VECTOR frontVec = VGet(sinf(m_Rot.y), 0.0f, cosf(m_Rot.y));
		VECTOR rightVec = VGet(cosf(m_Rot.y), 0.0f, -sinf(m_Rot.y));

		float stickX = (float)Input::GetLeftStickX() / 1000.0f;
		float stickY = (float)Input::GetLeftStickY() / 1000.0f;

		m_Move = MyMath::VecAdd(MyMath::VecScale(frontVec, -stickY), MyMath::VecScale(rightVec, stickX));

		m_Move = MyMath::VecScale(m_Move, m_Speed);

		if (m_Move.x == 0.0f && m_Move.z == 0.0f)
		{
			PlayAnimation(PLAYER_ANIMATION_STOP, true);
		}
		else
		{
			PlayAnimation(PLAYER_ANIMATION_WALK, true);

			//m_Rot.y = atan2f(m_Move.x, m_Move.z);
		}
	}

	if (Input::IsTriggerButton(Input::BUTTON_RB))
	{
		if (m_ActionType != ACTION_TYPE_NONE) return;

		PlayAnimation(PLAYER_ANIMATION_ATTACK, false);
		m_ActionType = ACTION_ATTACK;

		m_AttackHitFlag = true;
	}

	if (Input::IsTriggerButton(Input::BUTTON_B))
	{
		if (m_ActionType != ACTION_TYPE_NONE) return;

		PlayAnimation(PLAYER_ANIMATION_SKILL, false);
		m_ActionType = ACTION_SKILL;
		m_Power++;

		VECTOR playerFootPos = VGet(m_Pos.x, m_Pos.y - PLAYER_SIZE.y / 2, m_Pos.z);

		EffekseerManager::GetInstance()->PlayEffect(EFFEKSEER_SKILL, playerFootPos);
	}

	if (Input::IsTriggerButton(Input::BUTTON_LB))
	{
		if (m_ActionType != ACTION_TYPE_NONE) return;

		PlayAnimation(PLAYER_ANIMATION_SUPER_ATTACK, false);

		m_ActionType = ACTION_SUPER_ATTACK;

		m_AttackHitFlag = true;
	}

	if (m_ActionType == ACTION_SUPER_ATTACK)
	{
		m_Move.x = PLAYER_SUPER_ATTACK_MOVE_SPEED * sinf(m_Rot.y);
		m_Move.z = PLAYER_SUPER_ATTACK_MOVE_SPEED * cosf(m_Rot.y);
	}

	if (m_ActionType != ACTION_SUPER_ATTACK)
	{
		CameraBase* camera = CameraManager::GetInstance()->GetCamera(CAMERA);
		m_Rot.y = camera->GetRot().y;
	}

	if (m_Rot.y < 0)
	{
		m_Rot.y += DX_TWO_PI_F;
	}
	else if (m_Rot.y > DX_TWO_PI_F)
	{
		m_Rot.y -= DX_TWO_PI_F;
	}

	m_Move.y = m_Gravity;

	if (m_Randing)
	{
		m_Gravity = 0.0f;

		m_Move.y = -0.0001f;
	}
	else
	{
		m_Gravity -= PLAYER_GRAVITY;
		m_Move.y = m_Gravity;
	}

	m_Randing = false;

	UpdateAnimation();

	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);

	MV1RefreshCollInfo(m_Handle);

	DrawFormatString(0, 200, GetColor(255, 255, 255), "‰ñ“][%f, %f, %f]", m_Rot.x, m_Rot.y, m_Rot.z);
	DrawFormatString(0, 220, GetColor(255, 255, 255), "ˆÚ“®[%f, %f, %f]", m_Move.x, m_Move.y, m_Move.z);
}

void Player::PlayAnimation(PlayerAnimationType anim, bool isLoop)
{
	if (anim == m_NowAnimation) return;

	MV1DetachAnim(m_Handle, m_AnimationAttachIndex);

	m_AnimationAttachIndex = MV1AttachAnim(m_Handle, anim);

	m_AnimationTotalTime = m_AnimTotalTimes[anim];

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
			m_ActionType = ACTION_TYPE_NONE;
		}
		else
		{
			m_AnimationNowTime = m_AnimationTotalTime;
			m_ActionType = ACTION_TYPE_NONE;

			PlayAnimation(PLAYER_ANIMATION_STOP, true);
			
		}
	}
}