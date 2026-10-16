#include "ResultSceneUI.h"
#include "../CharacterManager.h"
#include "../../MyMath/MyMath.h"
#include "../../MyColor/MyColor.h"

namespace ResultSceneUI
{
	const VECTOR BOSS_FRAME_DEFAULT_POS = MyMath::Vec2D(450.0f, 300.0f);
	const VECTOR CHALLENGER_FRAME_DEFAULT_POS = MyMath::Vec2D(1150.0f, 300.0f);
	const int ICON_POS_OFFSET_X = 150;
	const VECTOR NAME_POS_OFFSET = MyMath::Vec2D(-55.0f, -40.0f);

	const double FRAME_SCALE_OFFSET = 1.7;
	const double ICON_SCALE_OFFSET = 0.7;

	const int FRAME_POS_Y_INTERVAL = 200;
	const int UI_NAME_SCALE = 84;

	int g_BossFrameHandle;
	int g_ChallengerFrameHandle;

	void Init()
	{
		g_BossFrameHandle = 0;
		g_ChallengerFrameHandle = 0;
	}

	void Load()
	{
		g_BossFrameHandle = LoadGraph("Data/UI/BattleScene/BossFrame.png");
		g_ChallengerFrameHandle = LoadGraph("Data/UI/BattleScene/ChallengerFrame.png");
	}

	void DrawFrame(CharacterBase* character)
	{
		int framePosYDiff = 0;

		bool isBoss = character->IsBoss();

		if (isBoss)
		{
			// フレーム
			DrawRotaGraph((int)BOSS_FRAME_DEFAULT_POS.x, (int)BOSS_FRAME_DEFAULT_POS.y, 
				FRAME_SCALE_OFFSET, 0.0, g_BossFrameHandle, TRUE);

			//アイコン
			DrawRotaGraph((int)BOSS_FRAME_DEFAULT_POS.x - ICON_POS_OFFSET_X, 
				(int)BOSS_FRAME_DEFAULT_POS.y, ICON_SCALE_OFFSET, 0.0, character->GetIconHandle(), false);
		}
		else
		{
			int index = character->GetIndex();

			int bossNum = CharacterManager::GetInstance()->GetBossNum();

			if (index < bossNum)
			{
				framePosYDiff = FRAME_POS_Y_INTERVAL * index;
			}
			else
			{
				framePosYDiff = FRAME_POS_Y_INTERVAL * (index - 1);
			}

			// フレーム
			DrawRotaGraph((int)CHALLENGER_FRAME_DEFAULT_POS.x, (int)CHALLENGER_FRAME_DEFAULT_POS.y + framePosYDiff, 
				FRAME_SCALE_OFFSET, 0.0, g_ChallengerFrameHandle, TRUE);

			//アイコン
			DrawRotaGraph((int)CHALLENGER_FRAME_DEFAULT_POS.x - ICON_POS_OFFSET_X, 
				(int)CHALLENGER_FRAME_DEFAULT_POS.y + framePosYDiff, ICON_SCALE_OFFSET, 0.0, character->GetIconHandle(), false);
		}

		unsigned int nameTextColor = COLOR_BLACK;

		string name = character->GetName();

		VECTOR pos = MyMath::VecZero();

		if (isBoss)
		{
			nameTextColor = COLOR_WHITE;

			pos.x = BOSS_FRAME_DEFAULT_POS.x + NAME_POS_OFFSET.x;
			pos.y = BOSS_FRAME_DEFAULT_POS.y + framePosYDiff + NAME_POS_OFFSET.y;

		}
		else
		{
			pos.x = CHALLENGER_FRAME_DEFAULT_POS.x + NAME_POS_OFFSET.x;
			pos.y = CHALLENGER_FRAME_DEFAULT_POS.y + framePosYDiff + NAME_POS_OFFSET.y;

		}		
	}
}