#include "BeastJumpWave.h"
#include <math.h>
#include "BulletParameter.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"

const VECTOR WAVE_SIZE = VGet(4.0f, 4.0f, 4.0f);
const float WAVE_SPREAD_SPEED = 1.8f;
const int WAVE_LIFE = 1;
const int WAVE_DAMAGE = 20;

BeastJumpWave::BeastJumpWave() : BulletBase()
{

}

BeastJumpWave::~BeastJumpWave()
{
	Fin();
}

void BeastJumpWave::Init()
{
	m_Type = BEAST_JUMP_WAVE;
}

void BeastJumpWave::Load()
{
	MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
}

void BeastJumpWave::Start()
{
	BulletBase::Start();

	m_Scale = VGet(1.0f, 1.0f, 1.0f);

	m_Active = true;
	m_IsBoss = true;

	m_Damage = WAVE_DAMAGE;

	m_Life = WAVE_LIFE;

	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));

	VECTOR aabbSize = VGet(WAVE_SIZE.x * m_Scale.x, WAVE_SIZE.y * m_Scale.y, WAVE_SIZE.z * m_Scale.z);
	m_AABB->SetSize(aabbSize);

	m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_Sphere->SetRadius(m_Scale.y / 2.0f);
}

void BeastJumpWave::Step()
{
	m_Scale.x += WAVE_SPREAD_SPEED;
	m_Scale.y += WAVE_SPREAD_SPEED;
	m_Scale.z += WAVE_SPREAD_SPEED;

	if (m_Scale.x > 70.0f)
	{
		m_Active = false;
	}

	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1SetScale(m_Handle, m_Scale);
	m_Sphere->SetRadius(m_Scale.y / 2.0f);

	MV1RefreshCollInfo(m_Handle);
}

