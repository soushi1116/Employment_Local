#include "Bullet.h"
#include "../Component.h"
#include "../GameObject.h"
#include "../../FPS/FPSManager.h"

Bullet::Bullet(GameObject* owner) : Component(owner)
{
	m_Type = BULLET_TYPE_NONE;

	m_MoveSpeed = 0.0f;

	m_LifeLimit = 0.0f;
	m_LifeTimer = 0.0f;

	m_Active = true;
}

Bullet::~Bullet()
{

}

void Bullet::Step()
{
	if (!m_Active) return;

	if (m_Physics != nullptr)
	{
		VECTOR forward = m_Physics->GetForward();

		m_Physics->AddMove(VScale(forward, m_MoveSpeed));
	}

	FPSSystem* fps = FPSManager::GetInstance()->GetFPS();
	float deltaTime = fps->GetDeltaTime();

	m_LifeTimer += deltaTime;
	if (m_LifeTimer >= m_LifeLimit)
	{
		m_Active = false;
		m_LifeTimer = 0.0f;
	}

	m_DamageCollision->SetPos(m_Physics->GetPos());
}