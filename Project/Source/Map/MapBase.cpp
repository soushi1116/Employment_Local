#include "MapBase.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"

const VECTOR DEFAULT_POS = VGet(0.0f, -10.0f, 0.0f);

const float STAGE_WIDTH = 85.0f;
const float STAGE_DEPTH = 85.0f;

MapBase::MapBase()
{
	m_Handle = 0;
	m_CollisionHandle = 0;
	m_Pos = MyMath::VecZero();
	m_Scale = MyMath::VecZero();
	m_AABB = nullptr;
	m_CollisionResult = {};
	m_Type = MAP_TYPE_NONE;
}

MapBase::~MapBase()
{
	Fin();
}

void MapBase::Start()
{
	m_Pos = DEFAULT_POS;
	m_Scale = VGet(STAGE_WIDTH, 0.0f, STAGE_DEPTH);

	/*m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, -0.0f, 0.0f));
	m_AABB->SetSize(VGet(FLOOR_WIDTH, FLOOR_HEIGHT, FLOOR_DEPTH));*/

	MV1SetupCollInfo(m_CollisionHandle);
}

void MapBase::Step()
{

}

void MapBase::Update()
{
	MV1SetPosition(m_Handle, m_Pos);
	MV1SetPosition(m_CollisionHandle, m_Pos);
}

void MapBase::Draw()
{
	SetUseAlphaTestFlag(TRUE);
	SetUseBackCulling(FALSE);
	MV1DrawModel(m_Handle);

#ifdef DEBUG
	MV1DrawModel(m_CollisionHandle);
#endif // DEBUG

	SetUseBackCulling(TRUE);
}

void MapBase::Fin()
{
	MV1TerminateCollInfo(m_CollisionHandle);
	MV1DeleteModel(m_Handle);
	MV1DeleteModel(m_CollisionHandle);
}

MV1_COLL_RESULT_POLY_DIM MapBase::CheckCollisionSphere(VECTOR pos, float r)
{
	MV1RefreshCollInfo(m_CollisionHandle, -1);

	return MV1CollCheck_Sphere(m_CollisionHandle, -1, pos, r);
}