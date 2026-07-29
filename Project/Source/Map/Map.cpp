#include "Map.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"

const VECTOR DEFAULT_POS = VGet(0.0f, -10.0f, 0.0f);

const float STAGE_WIDTH = 85.0f;
const float STAGE_DEPTH = 85.0f;

Map::Map()
{
	m_Handle = 0;
	m_CollisionHandle = 0;
	m_Pos = MyMath::VecZero();
	m_Scale = MyMath::VecZero();
	m_AABB = nullptr;
	m_CollisionResult = {};
}

Map::~Map()
{
	Fin();
}

void Map::Init()
{

}

void Map::Load()
{
	m_Handle = MV1LoadModel("Data/Map/TestStage.x");

	m_CollisionHandle = MV1LoadModel("Data/Map/TestStageCollision.x");
}

void Map::Start()
{
	m_Pos = DEFAULT_POS;
	m_Scale = VGet(STAGE_WIDTH, 0.0f, STAGE_DEPTH);

	/*m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, -0.0f, 0.0f));
	m_AABB->SetSize(VGet(FLOOR_WIDTH, FLOOR_HEIGHT, FLOOR_DEPTH));*/

	MV1SetupCollInfo(m_CollisionHandle);
}

void Map::Step()
{

}

void Map::Update()
{
	MV1SetPosition(m_Handle, m_Pos);
	MV1SetPosition(m_CollisionHandle, m_Pos);
}

void Map::Draw()
{
	SetUseBackCulling(FALSE);
	MV1DrawModel(m_Handle);
	SetUseBackCulling(TRUE);
}

void Map::Fin()
{
	MV1TerminateCollInfo(m_CollisionHandle);
	MV1DeleteModel(m_Handle);
	MV1DeleteModel(m_CollisionHandle);
}

MV1_COLL_RESULT_POLY_DIM Map::CheckCollisionSphere(VECTOR pos, float r)
{
	MV1RefreshCollInfo(m_CollisionHandle, -1);

	return MV1CollCheck_Sphere(m_CollisionHandle, -1, pos, r);
}