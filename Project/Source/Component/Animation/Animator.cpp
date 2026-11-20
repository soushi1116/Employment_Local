#include "Animator.h"
#include "Animation.h"
#include "../GameObject.h"
#include "../../FPS/FPSManager.h"

constexpr float ANIMATION_SPEED = 0.3f;

Animator::Animator(GameObject* owner)
	: Component(owner)
	, m_Time(0.0f)
	, m_CurrentIndex(-1)
	, m_IsFinish(false)
	, m_ModelHandle(-1)
	, m_CharacterType(CharacterType::CHARACTER_TYPE_NONE)
{

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

/// <summary>
/// アニメーション再生
/// </summary>
/// <param name="animType">アニメーションの種類</param>
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

	if (auto model = m_Model.lock())
	{
		m_ModelHandle = model->GetModelHandle();
	}

	if (m_CurrentIndex != -1)
	{
		MV1DetachAnim(m_ModelHandle, m_CurrentIndex);
		m_CurrentIndex = -1;
	}

	int motionIndex = m_NextAnim->GetAnimData().m_Index;

	m_CurrentIndex = MV1AttachAnim(m_ModelHandle, motionIndex);

	m_Time = 0.0f;
	m_IsFinish = false;

	m_CurrentAnim = m_NextAnim;
	m_NextAnim = nullptr;
}

/// <summary>
///  アニメーションの更新
/// </summary>
void Animator::UpdateAnim()
{
	m_Time += ANIMATION_SPEED;

	float totalTime = m_CurrentAnim->GetAnimData().m_TotalTime;

	if (m_Time >= totalTime && totalTime > 0.0f)
	{
		if (m_CurrentAnim->GetAnimData().m_IsLoopAnimation)
		{
			m_Time = fmodf(m_Time, totalTime);
		}
		else
		{
			if (!m_IsFinish)
			{
				m_IsFinish = true;
			}
		}
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