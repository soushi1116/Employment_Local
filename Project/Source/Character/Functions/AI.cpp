#include "DxLib.h"
#include "AI.h"
//#include "../CharacterManager.h"
#include "../../MyMath/MyMath.h"
#include "../../FPS/FPSManager.h"
#include "../../Item/ItemManager.h"

namespace AI
{
	//const float ITEM_DISTANCE = 80.0f;

	//CharacterBase* SearchTarget(CharacterBase* thisCharacter)
	//{
	//	CharacterBase* target = nullptr;

	//	//const auto& characterList = CharacterManager::GetInstance()->GetCharacterList();

	//	float minDistanceSq = FLT_MAX;

	//	VECTOR thisPos = thisCharacter->GetPos();
	//	VECTOR targetPos = MyMath::VecZero();

	//	/*if (thisCharacter->IsBoss())
	//	{
	//		for (auto& character : characterList)
	//		{
	//			if (character->IsBoss()) continue;
	//			if (character->IsDead()) continue;
	//			if (character->IsInvisible()) continue;

	//			VECTOR targetPos = character->GetPos();
	//			float diffX = targetPos.x - thisPos.x;
	//			float diffY = targetPos.y - thisPos.y;
	//			float diffZ = targetPos.z - thisPos.z;

	//			float currentDistanceSq = diffX * diffX + diffY * diffY + diffZ * diffZ;

	//			if (currentDistanceSq < minDistanceSq)
	//			{
	//				minDistanceSq = currentDistanceSq;
	//				target = character;
	//			}
	//		}
	//	}
	//	else
	//	{
	//		for (auto& character : characterList)
	//		{
	//			if (character->IsBoss())
	//			{
	//				target = character;

	//				break;
	//			}
	//		}
	//	}*/


	//	return target;
	//}

	//AIMoveType DecideMoveTypeBoss(CharacterBase* thisCharacter)
	//{
	//	AIMoveType result = MOVE_TYPE_NONE;

	//	auto missionList = MissionManager::GetInstance()->GetMissionList();

	//	ItemBase* nearestItem = thisCharacter->GetNearestItem();

	//	if (nearestItem != nullptr)
	//	{
	//		result = MOVE_TYPE_GET_ITEM;
	//	}
	//	else if (missionList.empty())
	//	{
	//		result = MOVE_TYPE_ESCAPE;
	//	}
	//	else
	//	{
	//		result = MOVE_TYPE_ATTACK;
	//	}

	//	return result;
	//}

	//AIMoveType DecideMoveTypeChallenger(CharacterBase* thisCharacter)
	//{
	//	AIMoveType result = MOVE_TYPE_NONE;

	//	int hp = thisCharacter->GetHP();
	//	int maxHp = thisCharacter->GetMaxHP();

	//	float hpPercentage = (float)hp / (float)maxHp;

	//	ItemBase* nearestItem = SearchNearestItem(thisCharacter);

	//	if (nearestItem != nullptr)
	//	{
	//		result = MOVE_TYPE_GET_ITEM;
	//	}
	//	else if (hpPercentage > 0.5f)
	//	{
	//		result = MOVE_TYPE_ATTACK;
	//	}
	//	else
	//	{
	//		result = MOVE_TYPE_ESCAPE;
	//	}

	//	return result;
	//}

	//ItemBase* SearchNearestItem(CharacterBase* thisCharacter)
	//{
	//	auto itemList = ItemManager::GetInstance()->GetItemList();

	//	ItemBase* resultItem = nullptr;

	//	VECTOR thisPos = thisCharacter->GetPos();

	//	VECTOR itemPos = MyMath::VecZero();

	//	float nearestDistance = ITEM_DISTANCE;
	//	float currentDistance = 0.0f;

	//	for (auto& item : itemList)
	//	{
	//		if (!item->IsActive()) continue;

	//		itemPos = item->GetPos();

	//		currentDistance = MyMath::VecLong(MyMath::VecCreate(thisPos, itemPos));

	//		if (currentDistance < nearestDistance)
	//		{
	//			nearestDistance = currentDistance;
	//			resultItem = item;
	//		}
	//	}

	//	return resultItem;
	//}
}