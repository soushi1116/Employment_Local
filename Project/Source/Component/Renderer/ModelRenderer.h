#pragma once
#include "../Component.h"
#include <memory>
#include "DxLib.h"

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
	void SetOpacity(float opacity) { m_Opacity = opacity; }
	void SetPosOffset(VECTOR offset) { m_PosOffset = offset; }

	int GetModelHandle() const { return m_ModelHandle; }

private:
	int m_ModelHandle = -1;
	int m_TextureHandle = -1;
	std::weak_ptr<Physics3D> m_Physics3D;

	float m_RotYOffset;
	float m_Opacity;

	VECTOR m_PosOffset;
};