#include "../Component.h"
#include "ModelRenderer.h"
#include "DxLib.h"
#include "../GameObject.h"
#include "../Physics/3DPhysics.h"

ModelRenderer::ModelRenderer(GameObject* owner, const char* filePath) : Component(owner)
{
	m_ModelHandle = MV1LoadModel(filePath);

	m_CompName = "Model";

	m_RotYOffset = 0.0f;
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
	m_Physics3D = m_Owner->GetComponent<Physics3D>().get();
}

void ModelRenderer::Draw()
{
	if (m_ModelHandle == -1) return;

	int currentTexture = MV1GetTextureGraphHandle(m_ModelHandle, 0);

	// テクスチャありかつ未割り当てのときのみ割り当て
	if (currentTexture != m_TextureHandle && m_TextureHandle != -1)
	{
		MV1SetTextureGraphHandle(m_ModelHandle, 0, m_TextureHandle, true);
	}

	MV1SetPosition(m_ModelHandle, m_Physics3D->GetPos());

	float dirAngleY = m_Physics3D->GetDirAngleY();
	VECTOR dirAngle = VAdd(MyMath::VecY(dirAngleY), MyMath::VecY(m_RotYOffset));
	MV1SetRotationXYZ(m_ModelHandle, dirAngle);
	MV1SetScale(m_ModelHandle, m_Physics3D->GetScale());
	
	MV1DrawModel(m_ModelHandle);
}

void ModelRenderer::SetTexure(const char* filePath)
{
	m_TextureHandle = LoadGraph(filePath);
}