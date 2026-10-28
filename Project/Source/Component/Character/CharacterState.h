#pragma once
#include <memory>
#include "../Component.h"

class GameObject;
class Timer;
class SpriteRenderer;

enum CharacterStateType
{
	STATE_POWER_UP,
	STATE_DEFFENCE_UP,
	STATE_BOOST,
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
	void SetType(CharacterStateType type) { m_Type = type; }

	bool IsActive() const { return m_Active; }
	CharacterStateType GetType() const { return m_Type; }

private:
	bool m_Active;
	CharacterStateType m_Type;
	std::weak_ptr<Timer> m_Timer;
};
