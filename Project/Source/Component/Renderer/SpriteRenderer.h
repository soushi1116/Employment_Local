#pragma once
#include "../Component.h"
#include <memory>

class GameObject;

class SpriteRenderer : public Component
{
public:
	SpriteRenderer(GameObject* owner, const char* filePath);

	~SpriteRenderer();

	void Start();
	void Draw();

	void SetPos(VECTOR pos) { m_RectTransform.m_Pos = pos; }
	void SetScale(VECTOR scale) { m_RectTransform.m_Scale = scale; }

private:
	struct RectTransform
	{
		VECTOR m_Pos;
		VECTOR m_Scale;
	};

	int m_SpriteHandle = -1;
	RectTransform m_RectTransform;
};