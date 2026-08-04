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

	void SetText(const char* text);
	void SetColor(unsigned int color);

private:
	char m_Text[UI_TEXT_MAX];
	int m_FontHandle;
	unsigned int m_Color;
};