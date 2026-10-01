#pragma once

class GameObject;
class Transform;
class BackGroundRenderer;
class ModelRenderer;
class SpriteRenderer;
class CharacterStatus;
class CharacterParameter;
class CharacterInput;

class Component
{
public:
	Component(GameObject* owner);
	virtual ~Component();

	virtual void Start();
	virtual void Update();
	virtual void Draw();

protected:
	GameObject* m_Owner;
};