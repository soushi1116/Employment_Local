#pragma once
#include <memory>
#include "../Component.h"
#include "DxLib.h"

class GameObject;
class Timer;
class SpriteRenderer;
class CharacterParameter;

enum CharacterStateType
{
	STATE_POWER_UP,
	STATE_DEFENCE_UP,
	STATE_BOOST,
	STATE_SPEED_UP,
	STATE_POISONED,
	STATE_INVISIBLE,

	STATE_TYPE_MAX,
	STATE_TYPE_NONE = -1
};

class CharacterState : public Component
{
public:
	CharacterState(GameObject* owner);
	~CharacterState();

public:
	void Start() override;
	void Update() override;

public:
	void SetActive(bool active) { m_Active = active; }
	void SetTimer(std::shared_ptr<Timer> timer) { m_Timer = timer; }
	void SetParent(std::weak_ptr<CharacterParameter> param) { m_ParentParameter = param; }
	void SetIcon(std::weak_ptr<SpriteRenderer> icon) { m_IconRenderer = icon; }
	void SetType(CharacterStateType type) { m_Type = type; }

	void SetIconPos(VECTOR pos);

	bool IsActive() const { return m_Active; }
	CharacterStateType GetType() const { return m_Type; }

private:
	bool m_Active;
	CharacterStateType m_Type;
	std::weak_ptr<Timer> m_Timer;
	std::weak_ptr<CharacterParameter> m_ParentParameter;
	std::weak_ptr<SpriteRenderer> m_IconRenderer;
};
