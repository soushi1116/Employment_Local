#pragma once
#include "../Component.h"
#include <memory>
#include <vector>
#include "Animation.h"
#include "../Character/CharacterParameter.h"

class GameObject;
class Animation;
class ModelRenderer;

class Animator : public Component
{
public:
	Animator(GameObject* owner);

	~Animator();

	void Start() override;
	void Update() override;

	void PlayAnim(CharacterAnimationType animType);
	void UpdateAnim();

	std::shared_ptr<Animation> GetAnim(CharacterAnimationType type);
	std::shared_ptr<Animation> GetCurrentAnim() { return m_CurrentAnim; }

	bool IsFinish() { return m_IsFinish; }

private:
	std::vector<std::shared_ptr<Animation>> m_Animations;

	std::shared_ptr<Animation> m_CurrentAnim;
	std::shared_ptr<Animation> m_NextAnim;

	float m_Time;
	int m_CurrentIndex;
	bool m_IsFinish;

	std::shared_ptr<ModelRenderer> m_Model;
	int m_ModelHandle;

	CharacterType m_CharacterType;
};