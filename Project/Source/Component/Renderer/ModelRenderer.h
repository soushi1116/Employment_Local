#pragma once
#include "../Component.h"
#include <memory>

class GameObject;
class Physics3D;

class ModelRenderer : public Component
{
public:
	ModelRenderer(GameObject* owner, const char* filePath);

	~ModelRenderer();

	void Start();
	void Draw();

	void SetTexure(const char* filePath);
	void SetRotYOffset(float offset) { m_RotYOffset = offset; }

	int GetModelHandle() const { return m_ModelHandle; }

private:
	int m_ModelHandle = -1;
	int m_TextureHandle = -1;
	std::shared_ptr<Physics3D> m_Physics3D;

	float m_RotYOffset;
};