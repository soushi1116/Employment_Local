#pragma once

#include "DxLib.h"

class CharacterBase;

namespace BattleSceneUI
{
	void Init();
	void Load();
	
	void DrawFrame(CharacterBase* character);
	void DrawGauges(CharacterBase* character);
}