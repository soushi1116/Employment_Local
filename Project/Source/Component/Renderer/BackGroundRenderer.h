#pragma once
#include "RendererBase.h"
#include <memory>

class GameObject;

class BackGroundRenderer : public RendererBase
{
public:
	BackGroundRenderer(GameObject* owner, const char* filePath);

	~BackGroundRenderer();

	void Start();
	void Draw();

private:
	int m_BackGroundHandle = -1;
};