#include "Conveyor.h"
#include "../GameObject.h"
#include "../Component.h"
#include "../../Scene/SceneManager.h"

constexpr float ARROW_OBJ_INTERVAL = 50.0f;
constexpr float CONVEYOR_MOVE_SPEED = 0.5f;

Conveyor::Conveyor(GameObject* owner)
	: GimmickBase(owner)
	, m_Direction(MyMath::VecZero())
	, m_MaxVec(MyMath::VecZero())
	, m_Length(0.0f)
	, m_ArrowCreated(false)
{

}

Conveyor::~Conveyor()
{

}

void Conveyor::Start()
{
	m_MaxVec = VScale(m_Direction, m_Length * 0.5f);
}

void Conveyor::Step()
{
	auto physicsShared = m_Physics.lock();

	if (!physicsShared) return;

	if (!m_ArrowCreated)
	{
		int arrowNum = static_cast<int>(m_Length / ARROW_OBJ_INTERVAL);

		for (int i = 0; i < arrowNum; i++)
		{
			auto arrowObj = std::make_shared<GameObject>();
			arrowObj->AddTag(TAG_ARROW);
			auto arrowPhysics = arrowObj->AddComponent<Physics3D>();

			VECTOR defaultPos = physicsShared->GetPos();
			float posOffset = m_Length * 0.5f - (i + 1) * ARROW_OBJ_INTERVAL;
			VECTOR posOffsetVec = VScale(m_Direction, posOffset);
			VECTOR spawnPos = VAdd(defaultPos, posOffsetVec);

			arrowPhysics->SetPos(spawnPos);

			float angleY = atan2f(m_Direction.x, m_Direction.z);

			arrowPhysics->SetDirAngleY(angleY);

			auto arrowModel = arrowObj->AddComponent<ModelRenderer>("Data/Gimmick/ConveyorArrow.x");

			m_ArrowObjs.push_back(arrowObj);

			SceneManager::GetInstance()->GetNowScene()->Instantiate(arrowObj);
		}

		m_ArrowCreated = true;
	}

	for (const auto& arrowObj : m_ArrowObjs)
	{
		auto arrowShared = arrowObj.lock();

		if (!arrowShared) continue;

		auto arrowPhysics = arrowShared->GetComponent<Physics3D>();

		VECTOR currentVec = MyMath::VecCreate(physicsShared->GetPos(), arrowPhysics->GetPos());

		VECTOR moveVec = VScale(m_Direction, CONVEYOR_MOVE_SPEED);
		
		if (VSize(currentVec) > VSize(m_MaxVec))
		{
			moveVec = VAdd(moveVec, VScale(m_Direction, -m_Length));
		}

		arrowPhysics->AddMove(moveVec);
	}

	auto characters = SceneManager::GetInstance()->GetNowScene()->GetGameObjectsByTag(TAG_CHARACTER);

	for (const auto& character : characters)
	{
		auto characterPhysics = character->GetComponent<Physics3D>();

		// “–‚½‚è”»’è
	}
}