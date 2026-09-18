#pragma once

#include "DxLib.h"

class CharacterBase;

namespace ResultSceneUI
{
	void Init();
	void Load();

	void DrawFrame(CharacterBase* character);
}