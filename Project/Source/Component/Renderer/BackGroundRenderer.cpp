#include "../Component.h"
#include "BackGroundRenderer.h"
#include "DxLib.h"
#include "../GameObject.h"
#include "../Transform.h"
#include "../../MyMath/MyMath.h"

BackGroundRenderer::BackGroundRenderer(GameObject* owner, const char* filePath) : Component(owner)
{
	m_BackGroundHandle = LoadGraph(filePath);

	m_CompName = "BackGround";
}

BackGroundRenderer::~BackGroundRenderer()
{
	if (m_BackGroundHandle != -1)
	{
		DeleteGraph(m_BackGroundHandle);
	}
}

void BackGroundRenderer::Start()
{

}

void BackGroundRenderer::Draw()
{
	if (m_BackGroundHandle == -1) return;

	DrawGraph(0, 0, m_BackGroundHandle, TRUE);
}