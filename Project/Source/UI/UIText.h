#pragma once
#include "DxLib.h"
#include "UIParameter.h"
#include "UIBase.h"

const int UI_TEXT_MAX = 256;

class UIText : public UIBase
{
public:
	UIText();
	~UIText();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Draw() override;

	void SetText(const char* text) { strcpy_s(m_Text, text); }
	void SetColor(unsigned int color) { m_Color = color; }
	void SetPos(VECTOR pos) { m_Pos = pos; }
	void SetFontType(FontHandleType type) { m_FontType = type; }

private:
	char m_Text[UI_TEXT_MAX];
	int m_FontHandle;
	FontHandleType m_FontType;
	unsigned int m_Color;
};