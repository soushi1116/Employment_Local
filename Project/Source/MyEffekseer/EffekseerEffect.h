#pragma once
#include "EffekseerParameter.h"

#include "DxLib.h"

class BulletBase;
class CharacterBase;

class EffekseerEffect
{
public:
	EffekseerEffect();
	~EffekseerEffect();

public:
	virtual void Step();
	void Update();
	void Fin();

	void Play(int handle);
	void Stop();

	bool IsActive() const { return m_Active; }

	void SetActive(bool active) { m_Active = active; }
	void SetPos(VECTOR pos) { m_Pos = pos; }

	void SetParentBullet(BulletBase* bullet) { m_ParentBullet = bullet; }
	void SetParentCharacter(CharacterBase* character) { m_ParentCharacter = character; }
	void SetType(EffekseerEffectType type) { m_Type = type; }

	EffekseerEffectType GetType() { return m_Type; }

protected:
	bool m_Active;
	int m_Handle;
	VECTOR m_Pos;

	BulletBase* m_ParentBullet;
	CharacterBase* m_ParentCharacter;

	EffekseerEffectType m_Type;
};