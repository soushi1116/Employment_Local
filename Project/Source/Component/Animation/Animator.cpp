#include "Animator.h"
#include "Animation.h"
#include "../GameObject.h"
#include "../../FPS/FPSManager.h"

const float ANIMATION_SPEED = 0.2f;

Animator::Animator(GameObject* owner) : Component(owner)
{
	m_Time = 0.0f;
	m_CurrentIndex = -1;

	m_ModelHandle = -1;

	m_CharacterType = CharacterType::CHARACTER_TYPE_NONE;
}

Animator::~Animator()
{

}

void Animator::Start()
{
	m_CharacterType = m_Owner->GetComponent<CharacterParameter>()->GetType();
	m_Model = m_Owner->GetComponent<ModelRenderer>();

	m_CurrentAnim = std::make_shared<Animation>();
	m_CurrentAnim->SetAnimData(m_CharacterType, CharacterAnimationType::ANIMATION_NONE);
}

void Animator::Update()
{
	UpdateAnim();
}

void Animator::PlayAnim(CharacterAnimationType animType)
{
	if (m_CurrentAnim != nullptr && animType == m_CurrentAnim->GetAnimData().m_AnimType) return;

	m_NextAnim = GetAnim(animType);

	if (m_NextAnim == nullptr)
	{
		m_NextAnim = std::make_shared<Animation>();
		m_NextAnim->SetAnimData(m_CharacterType, animType);

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
	//FPSSystem* fps = FPSManager::GetInstance()->GetFPS();

	//float deltaTime = fps->GetDeltaTime();

	m_Time += ANIMATION_SPEED;;

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