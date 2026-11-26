#include "Conveyor.h"
#include "../GameObject.h"
#include "../Component.h"

constexpr float ARROW_OBJ_INTERVAL = 50.0f;
constexpr float CONVEYOR_MOVE_SPEED = 10.0f;

Conveyor::Conveyor(GameObject* owner)
	: GimmickBase(owner)
	, m_Direction(MyMath::VecZero())
	, m_Length(0.0f)
{

}

Conveyor::~Conveyor()
{

}

void Conveyor::Start()
{
	for (float i = 0.0f; i < m_Length; i += ARROW_OBJ_INTERVAL)
	{
		auto arrowObj = std::make_shared<GameObject>();
		auto arrowPhysics = arrowObj->AddComponent<Physics3D>();
		// ƒ‚ƒfƒ‹ì¬
		auto arrowModel = arrowObj->AddComponent<ModelRenderer>("");

		m_ArrowObjs.push_back(arrowObj);
	}
}

void Conveyor::Update()
{
	// ˆÚ“®
	// BoxCollision‚ª•K—v

	for (const auto& arrowObj : m_ArrowObjs)
	{
		auto arrowShared = arrowObj.lock();

		if (!arrowShared) continue;

		auto arrowPhysics = arrowShared->GetComponent<Physics3D>();

		arrowPhysics->AddMove(VScale(m_Direction, CONVEYOR_MOVE_SPEED));
	}
}