#include "Bullet.h"
#include "../Component.h"
#include "../GameObject.h"
#include "../../FPS/FPSManager.h"

Bullet::Bullet(GameObject* owner)
	: Component(owner)
	, m_Type(BULLET_TYPE_NONE)
	, m_MoveSpeed(0.0f)
	, m_LifeLimit(0.0f)
	, m_LifeTimer(0.0f)
	, m_Active(true)
{

}

Bullet::~Bullet()
{

}

void Bullet::Step()
{
	if (!m_Active) return;

	auto physics = m_Physics.lock();
	auto damageCollision = m_DamageCollision.lock();

	if (!physics || !damageCollision) return;

	FPSSystem* fps = FPSManager::GetInstance()->GetFPS();
	float deltaTime = fps->GetDeltaTime();

	m_LifeTimer += deltaTime;

	// Žõ–½‚ªs‚«‚½‚çÁ–Å
	if (m_LifeTimer >= m_LifeLimit)
	{
		m_Active = false;
		m_LifeTimer = 0.0f;
		return;
	}

	VECTOR forward = physics->GetForward();

	physics->AddMove(VScale(forward, m_MoveSpeed));

	damageCollision->SetPos(physics->GetPos());
}