#pragma once

#include "DxLib.h"
#include "../CharacterParameter.h"

class CharacterBase;

namespace AI
{
	CharacterBase* SearchTarget(CharacterBase* thisCharacter);
	AIMoveType DecideMoveTypeBoss(CharacterBase* thisCharacter);
	AIMoveType DecideMoveTypeChallenger(CharacterBase* thisCharacter);
}
