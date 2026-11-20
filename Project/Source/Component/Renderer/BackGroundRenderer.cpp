#include "../Component.h"
#include "BackGroundRenderer.h"
#include "DxLib.h"
#include "../GameObject.h"
#include "../../MyMath/MyMath.h"

BackGroundRenderer::BackGroundRenderer(GameObject* owner, const char* filePath)
	: RendererBase(owner, filePath)
	, m_BackGroundHandle(LoadGraph(filePath))
{

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
	m_RayerIndex = 1;
}

void BackGroundRenderer::Draw()
{
	if (m_BackGroundHandle == -1) return;

	DrawGraph(0, 0, m_BackGroundHandle, TRUE);
}