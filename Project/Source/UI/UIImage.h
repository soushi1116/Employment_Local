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
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

};