#pragma once
#include "../Component.h"
#include <memory>

class GameObject;

class BackGroundRenderer : public Component
{
public:
	BackGroundRenderer(GameObject* owner, const char* filePath);

	~BackGroundRenderer();

	void Start();
	void Draw();

private:
	int m_BackGroundHandle = -1;
};