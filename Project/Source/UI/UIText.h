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
	void Load(int scale) override;
	void Start() override;
	void Step() override;
	void Draw() override;

	void SetText(const char* text) { strcpy_s(m_Text, text); }
	void SetColor(unsigned int color) { m_Color = color; }
	void SetPos(VECTOR pos) { m_Pos = pos; }

private:
	char m_Text[UI_TEXT_MAX];
	int m_FontHandle;
	unsigned int m_Color;
};