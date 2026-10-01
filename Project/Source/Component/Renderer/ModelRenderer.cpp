#include "../Component.h"
#include "ModelRenderer.h"
#include "DxLib.h"
#include "../GameObject.h"
#include "../Transform.h"

ModelRenderer::ModelRenderer(GameObject* owner, const char* filePath) : Component(owner)
{
	m_ModelHandle = MV1LoadModel(filePath);

	if (m_ModelHandle != -1)
	{
		
	}

}

ModelRenderer::~ModelRenderer()
{
	if (m_ModelHandle != -1)
	{
		MV1DeleteModel(m_ModelHandle);
	}
}

void ModelRenderer::Start()
{
	m_Transform = m_Owner->GetComponent<Transform>();
}

void ModelRenderer::Draw()
{
	if (!m_Transform || m_ModelHandle == -1) return;

	MV1SetPosition(m_ModelHandle, m_Transform->GetPos());
	MV1SetRotationXYZ(m_ModelHandle, m_Transform->GetRot());
	MV1SetScale(m_ModelHandle, m_Transform->GetScale());
	
	MV1DrawModel(m_ModelHandle);
}