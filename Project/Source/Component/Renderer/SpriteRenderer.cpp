#include "../Component.h"
#include "SpriteRenderer.h"
#include "DxLib.h"
#include "../GameObject.h"
#include "../../MyMath/MyMath.h"

SpriteRenderer::SpriteRenderer(GameObject* owner, const char* filePath) : Component(owner)
{
	m_SpriteHandle = LoadGraph(filePath);
	//m_Transform = m_Owner->GetComponent<Transform>();
	m_CompName = "Sprite";
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
	//m_Transform = m_Owner->GetComponent<Transform>();
}

void SpriteRenderer::Draw()
{
	/*if (!m_Transform || m_SpriteHandle == -1) return;

	MyMath::VECTOR_INT pos = MyMath::Vec2DInt((int)m_Transform->GetPos().x, (int)m_Transform->GetPos().y);

	DrawRotaGraph(pos.x, pos.y, 1.0, 0.0, m_SpriteHandle, TRUE);*/
}