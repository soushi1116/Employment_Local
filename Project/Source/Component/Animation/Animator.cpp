#include "Animator.h"
#include "Animation.h"
#include "../GameObject.h"
#include "../../FPS/FPSManager.h"

Animator::Animator(GameObject* owner) : Component(owner)
{
	m_Time = 0.0f;
	m_CurrentIndex = -1;

	m_ModelHandle = -1;
}

Animator::~Animator()
{

}

void Animator::PlayAnim(CharacterAnimationType type, bool isLoop)
{
	if (m_CurrentAnim != nullptr && type == m_CurrentAnim->GetAnimData().m_Type) return;

	m_NextAnim = GetAnim(type);

	if (m_NextAnim == nullptr)
	{
		m_NextAnim = std::make_shared<Animation>();
		m_NextAnim->SetAnimData(type);

		m_Animations.push_back(m_NextAnim);
	}

	m_ModelHandle = m_Model->GetModelHandle();

	if (m_CurrentIndex != -1)
	{
		MV1DetachAnim(m_ModelHandle, m_CurrentIndex);
		m_CurrentIndex = -1;
	}

	int motionIndex = m_NextAnim->GetAnimData().m_Index;
	m_CurrentIndex = MV1AttachAnim(m_ModelHandle, motionIndex);

	m_Time = 0.0f;

	m_CurrentAnim = m_NextAnim;
	m_NextAnim = nullptr;
}

void Animator::UpdateAnim()
{
	FPSSystem* fps = FPSManager::GetInstance()->GetFPS();

	float deltaTime = fps->GetDeltaTime();

	m_Time += deltaTime;

	float totalTime = m_CurrentAnim->GetAnimData().m_TotalTime;

	if (m_Time >= totalTime)
	{
		m_Time = fmodf(m_Time, totalTime);
	}

	MV1SetAttachAnimTime(m_ModelHandle, m_CurrentIndex, m_Time);
}

std::shared_ptr<Animation> Animator::GetAnim(CharacterAnimationType type)
{
	for (const auto& anim : m_Animations)
	{
		if (anim->GetType() == type)
		{
			return anim;
		}
	}

	return nullptr;
}