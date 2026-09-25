#pragma once
#include "DxLib.h"
#include "UIParameter.h"
#include "UIBase.h"

class UIImage : public UIBase
{
public:
	UIImage();
	~UIImage();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

};