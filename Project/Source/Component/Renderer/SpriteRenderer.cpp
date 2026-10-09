#include "../Component.h"
#include "SpriteRenderer.h"
#include "DxLib.h"
#include "../GameObject.h"
#include "../../MyMath/MyMath.h"

SpriteRenderer::SpriteRenderer(GameObject* owner, const char* filePath) : Component(owner)
{
	m_SpriteHandle = LoadGraph(filePath);
	
	m_CompName = "Sprite";

	m_RectTransform.m_Pos = MyMath::VecZero();
	m_RectTransform.m_Scale = MyMath::VecZero();
}

SpriteRenderer::~SpriteRenderer()
{
	if (m_SpriteHandle != -1)
	{
		DeleteGraph(m_SpriteHandle);
	}
}

void SpriteRenderer::Start()
{
	
}

void SpriteRenderer::Draw()
{
	int posX = static_cast<int>(m_RectTransform.m_Pos.x);
	int posY = static_cast<int>(m_RectTransform.m_Pos.y);

	DrawRotaGraph(posX, posY, 1.0, 0.0, m_SpriteHandle, TRUE);
}