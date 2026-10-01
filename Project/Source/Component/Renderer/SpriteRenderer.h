#pragma once
#include "../Component.h"
#include <memory>

class GameObject;
class Transform;

class SpriteRenderer : public Component
{
public:
	SpriteRenderer(GameObject* owner, const char* filePath);

	~SpriteRenderer();

	void Start();
	void Draw();

private:
	int m_SpriteHandle = -1;
	std::shared_ptr<Transform> m_Transform;
};