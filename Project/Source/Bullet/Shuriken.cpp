#include "Shuriken.h"
#include <math.h>
#include "BulletParameter.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../MyEffekseer/EffekseerManager.h"
#include "../MyEffekseer/EffekseerEffect.h"

const VECTOR SHURIKEN_SIZE = VGet(4.0f, 4.0f, 4.0f);
const float SHURIKEN_MOVE_SPEED = 1.0f;
const float SHURIKEN_ROTATE_SPEED = 0.1f;
const int SHURIKEN_LIFE = 10;
const int SHURIKEN_DAMAGE = 30;

Shuriken::Shuriken() : BulletBase()
{

}

Shuriken::~Shuriken()
{
	Fin();
}

void Shuriken::Init()
{
	m_Type = SHURIKEN;
}

void Shuriken::Load()
{
	m_Handle = MV1LoadModel("Data/Bullet/Shuriken.x");

	MV1SetupCollInfo(m_Handle, -1, 8, 8, 8);
}

void Shuriken::Start()
{
	BulletBase::Start();

	m_Scale = VGet(1.0f, 1.0f, 1.0f);

	m_Active = true;
	m_IsBoss = false;

	m_Damage = SHURIKEN_DAMAGE;

	m_Life = SHURIKEN_LIFE;

	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));

	VECTOR aabbSize = VGet(SHURIKEN_SIZE.x * m_Scale.x, SHURIKEN_SIZE.y * m_Scale.y, SHURIKEN_SIZE.z * m_Scale.z);
	m_AABB->SetSize(aabbSize);

	m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_Sphere->SetRadius(SHURIKEN_SIZE.y * m_Scale.y / 2.0f);

	/*EffekseerEffect* effect = EffekseerManager::GetInstance()->PlayEffect(EFFEKSEER_BOT_BEAM, m_Pos);
	effect->SetParentBullet(this);*/
}

void Shuriken::Step()
{
	m_Move = VGet(0.0f, 0.0f, 0.0f);

	m_Rot.y += SHURIKEN_ROTATE_SPEED;

	if (m_Rot.y > DX_TWO_PI_F)
	{
		m_Rot.y -= DX_TWO_PI_F;
	}

	m_Move.x = SHURIKEN_MOVE_SPEED * sinf(m_Dir.y);
	m_Move.z = SHURIKEN_MOVE_SPEED * cosf(m_Dir.y);

	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1SetScale(m_Handle, m_Scale);

	MV1RefreshCollInfo(m_Handle);
}

