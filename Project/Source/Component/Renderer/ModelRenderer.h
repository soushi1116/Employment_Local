#pragma once
#include "../Component.h"
#include <memory>

class GameObject;
class _3DPhysics;

class ModelRenderer : public Component
{
public:
	ModelRenderer(GameObject* owner, const char* filePath);

	~ModelRenderer();

	void Start();
	void Draw();

	void SetTexure(const char* filePath);

private:
	int m_ModelHandle = -1;
	int m_TextureHandle = -1;
	std::shared_ptr<_3DPhysics> m_3DPhysics;
};