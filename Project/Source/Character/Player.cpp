#include "Player.h"
#include "CharacterParameter.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"

const float PLAYER_ROTATION_SPEED = 0.1f;
const float PLAYER_MOVE_SPEED = 0.1f;
const float PLAYER_GRAVITY = 0.01f;

const float PLAYER_WIDTH = 2.0f;
const float PLAYER_HEIGHT = 2.0f;
const float PLAYER_DEPTH = 2.0f;

Player::Player() : CharacterBase()
{

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
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_AABB->SetSize(VGet(PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_DEPTH));
}

void Player::Step()
{
	m_Move = VGet(0.0f, 0.0f, 0.0f);

	if (Input::IsInputKey(Input::KEY_LEFT))
	{
		m_Rot.y -= PLAYER_ROTATION_SPEED;
	}
	if (Input::IsInputKey(Input::KEY_RIGHT))
	{
		m_Rot.y += PLAYER_ROTATION_SPEED;
	}

	if (m_Rot.y < 0.0f)
	{
		m_Rot.y += DX_TWO_PI_F;
	}
	else if (m_Rot.y > DX_TWO_PI_F)
	{
		m_Rot.y -= DX_TWO_PI_F;
	}

	if (Input::IsInputKey(Input::KEY_UP))
	{
		VECTOR front = MyMath::VecForwardZX(m_Rot.y);

		m_Move = MyMath::VecScale(front, PLAYER_MOVE_SPEED);
	}

	m_Move.y = m_Gravity;

	if (!m_Randing) m_Gravity -= PLAYER_GRAVITY;
}