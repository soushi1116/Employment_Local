#include "Floor.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"

const VECTOR DEFAULT_POS = VGet(0.0f, -12.0f, 0.0f);

const float FLOOR_WIDTH = 60.0f;
const float FLOOR_HEIGHT = 2.0f;
const float FLOOR_DEPTH = 60.0f;

Floor::Floor()
{
	m_Handle = 0;
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
	m_Handle = MV1LoadModel("Data/Map/Floor.x");
}

void Floor::Start()
{
	m_Pos = DEFAULT_POS;

	/*m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, -0.0f, 0.0f));
	m_AABB->SetSize(VGet(FLOOR_WIDTH, FLOOR_HEIGHT, FLOOR_DEPTH));*/

	MV1SetupCollInfo(m_Handle);
}

void Floor::Step()
{

}

void Floor::Update()
{
	MV1SetPosition(m_Handle, m_Pos);
}

void Floor::Draw()
{
	MV1DrawModel(m_Handle);
}

void Floor::Fin()
{
	MV1TerminateCollInfo(m_Handle);
	MV1DeleteModel(m_Handle);
}

MV1_COLL_RESULT_POLY_DIM Floor::CheckCollisionSphere(VECTOR pos, float r)
{
	MV1RefreshCollInfo(m_Handle, -1);

	return MV1CollCheck_Sphere(m_Handle, -1, pos, r);
}