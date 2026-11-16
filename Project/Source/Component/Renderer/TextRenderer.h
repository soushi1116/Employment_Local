#pragma once
#include "DxLib.h"
#include "RendererBase.h"
#include <memory>
#include "../../Managers/RendererManager/RendererManager.h"

const int UI_TEXT_MAX = 256;

class GameObject;

class TextRenderer : public RendererBase
{
public:
	TextRenderer(GameObject* owner, const char* filePath);
	~TextRenderer();

public:
	void Start() override;
	void Step() override;
	void Draw() override;

	void SetText(const char* text) { strcpy_s(m_Text, text); }
	void SetColor(unsigned int color) { m_Color = color; }
	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetFontType(FontHandleType type) { m_FontType = type; }

	VECTOR GetPos() const { return m_Pos; }

private:
	char m_Text[UI_TEXT_MAX];
	int m_FontHandle;

	unsigned int m_Color;
	
	VECTOR m_Pos;

	float m_Alpha;
	bool m_Active;

	int m_SpriteHandle = -1;

	FontHandleType m_FontType;
};