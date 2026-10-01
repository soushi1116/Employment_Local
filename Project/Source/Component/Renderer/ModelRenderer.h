#pragma once
#include "../Component.h"
#include <memory>

class GameObject;
class Transform;

class ModelRenderer : public Component
{
public:
	ModelRenderer(GameObject* owner, const char* filePath);

	~ModelRenderer();

	void Start();
	void Draw();

private:
	int m_ModelHandle = -1;
	std::shared_ptr<Transform> m_Transform;
};