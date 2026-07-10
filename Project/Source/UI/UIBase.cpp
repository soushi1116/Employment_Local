#include "UIBase.h"
#include "../MyMath/MyMath.h"

UIBase::UIBase()
{
	m_Pos = MyMath::VecZero();
	m_Handle = 0;
	m_Type = UI_TYPE_NONE;
	m_Name = UI_NAME_NONE;
}

UIBase::~UIBase()
{
	Fin();
}

void UIBase::Update()
{

}

void UIBase::Draw()
{
	DrawRotaGraph(m_Pos.x, m_Pos.y, 1.0, 0.0, m_Handle, TRUE);
}

void UIBase::Fin()
{
	DeleteGraph(m_Handle);
}