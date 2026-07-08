#include "BotBeam.h"
#include <math.h>
#include "BulletParameter.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"

const VECTOR BOT_BEAM_SIZE = VGet(4.0f, 4.0f, 4.0f);
const float BOT_BEAM_SPEED = 1.0f;

BotBeam::BotBeam() : BulletBase()
{

}

BotBeam::~BotBeam()
{
	Fin();
}

void BotBeam::Init()
{
	m_Type = BOT_BEAM;
}

void BotBeam::Load()
{
	m_Handle = MV1LoadModel("Data/Bullet/BotBeam.x");

	MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
}

void BotBeam::Start()
{
	m_Scale = VGet(1.0f, 1.0f, 1.0f);

	m_Active = true;

	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));

	VECTOR aabbSize = VGet(BOT_BEAM_SIZE.x * m_Scale.x, BOT_BEAM_SIZE.y * m_Scale.y, BOT_BEAM_SIZE.z * m_Scale.z);
	m_AABB->SetSize(aabbSize);

	m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_Sphere->SetRadius(BOT_BEAM_SIZE.y * m_Scale.y / 2.0f);
}

void BotBeam::Step()
{
	m_Move = VGet(0.0f, 0.0f, 0.0f);

	m_Move.x = BOT_BEAM_SPEED * sinf(m_Rot.y);
	m_Move.z = BOT_BEAM_SPEED * cosf(m_Rot.y);

	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1SetScale(m_Handle, m_Scale);

	MV1RefreshCollInfo(m_Handle);
}

