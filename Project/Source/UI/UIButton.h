#pragma once
#include "DxLib.h"
#include "UIParameter.h"
#include "UIBase.h"


class UIButton : public UIBase
{
public:
	UIButton();
	~UIButton();

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

protected:
};