#include "Floor.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"

const VECTOR DEFAULT_POS = VGet(0.0f, -10.0f, 0.0f);

const float FLOOR_WIDTH = 60.0f;
const float FLOOR_HEIGHT = 2.0f;
const float FLOOR_DEPTH = 60.0f;

Floor::Floor()
{
	m_Handle = 0;
	m_CollisionHandle = 0;
	m_Pos = MyMath::VecZero();
	m_AABB = nullptr;
	m_CollisionResult = {};
}

Floor::~Floor()
{
	Fin();
}

void Floor::Init()
{

}

void Floor::Load()
{
	m_Handle = MV1LoadModel("Data/Map/TestStage.x");

	m_CollisionHandle = MV1LoadModel("Data/Map/TestStageCollision.x");
}

void Floor::Start()
{
	m_Pos = DEFAULT_POS;

	/*m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, -0.0f, 0.0f));
	m_AABB->SetSize(VGet(FLOOR_WIDTH, FLOOR_HEIGHT, FLOOR_DEPTH));*/

	MV1SetupCollInfo(m_CollisionHandle);
}

void Floor::Step()
{

}

void Floor::Update()
{
	MV1SetPosition(m_Handle, m_Pos);
	MV1SetPosition(m_CollisionHandle, m_Pos);
}

void Floor::Draw()
{
	SetUseBackCulling(FALSE);
	MV1DrawModel(m_Handle);
	SetUseBackCulling(TRUE);
}

void Floor::Fin()
{
	MV1TerminateCollInfo(m_CollisionHandle);
	MV1DeleteModel(m_Handle);
	MV1DeleteModel(m_CollisionHandle);
}

MV1_COLL_RESULT_POLY_DIM Floor::CheckCollisionSphere(VECTOR pos, float r)
{
	MV1RefreshCollInfo(m_CollisionHandle, -1);

	return MV1CollCheck_Sphere(m_CollisionHandle, -1, pos, r);
}