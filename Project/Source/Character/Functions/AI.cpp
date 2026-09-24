#include "DxLib.h"
#include "AI.h"
#include "../CharacterBase.h"
#include "../CharacterManager.h"
#include "../../MyMath/MyMath.h"
#include "../../FPS/FPSManager.h"

namespace AI
{
	CharacterBase* SearchTarget(CharacterBase* thisCharacter)
	{
		CharacterBase* target = nullptr;

		const auto& characterList = CharacterManager::GetInstance()->GetCharacterList();

		float minDistanceSq = FLT_MAX;

		VECTOR thisPos = thisCharacter->GetPos();
		VECTOR targetPos = MyMath::VecZero();

		if (thisCharacter->IsBoss())
		{
			for (auto character : characterList)
			{
				if (character->IsBoss()) continue;
				if (character->IsDead()) continue;
				if (character->IsInvisible()) continue;

				VECTOR targetPos = character->GetPos();
				float diffX = targetPos.x - thisPos.x;
				float diffY = targetPos.y - thisPos.y;
				float diffZ = targetPos.z - thisPos.z;

				float currentDistanceSq = diffX * diffX + diffY * diffY + diffZ * diffZ;

				if (currentDistanceSq < minDistanceSq)
				{
					minDistanceSq = currentDistanceSq;
					target = character;
				}
			}
		}
		else
		{
			for (auto character : characterList)
			{
				if (character->IsBoss())
				{
					target = character;

					break;
				}
			}
		}


		return target;
	}
}