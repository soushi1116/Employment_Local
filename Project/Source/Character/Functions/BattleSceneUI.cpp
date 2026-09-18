#include "BattleSceneUI.h"
#include "../CharacterManager.h"
#include "../../MyMath/MyMath.h"

namespace BattleSceneUI
{
	const int FRAME_POS_Y_INTERVAL = 150;

	const VECTOR FRAME_DEFAULT_POS = MyMath::Vec2D(175.0f, 50.0f);
	const VECTOR UI_SKILL_POS = VGet(175.0f, 775.0f, 0.0f);
	const VECTOR UI_SUPER_ATTACK_POS = VGet(475.0f, 775.0f, 0.0f);

	const float UI_SKILL_AND_SUPER_ATTACK_RADIUS = 75.0f;
	const double FRAME_SCALE_OFFSET = 1.0;
	const double ICON_SCALE_OFFSET = 0.4;

	int g_SkillHandle;
	int g_SuperAttackHandle;
	int g_SkillGaugeHandle;
	int g_SuperAttackGaugeHandle;

	int g_BossFrameHandle;
	int g_ChallengerFrameHandle;

	void Init()
	{
		g_BossFrameHandle = 0;
		g_ChallengerFrameHandle = 0;
		g_SkillHandle = 0;
		g_SuperAttackHandle = 0;
		g_SkillGaugeHandle = 0;
		g_SuperAttackGaugeHandle = 0;
	}

	void Load()
	{
		g_BossFrameHandle = LoadGraph("Data/UI/BattleScene/BossFrame.png");
		g_ChallengerFrameHandle = LoadGraph("Data/UI/BattleScene/ChallengerFrame.png");
		g_SkillHandle = LoadGraph("Data/UI/BattleScene/Skill.png");;
		g_SuperAttackHandle = LoadGraph("Data/UI/BattleScene/SuperAttack.png");
		g_SkillGaugeHandle = LoadGraph("Data/UI/BattleScene/SkillGauge.png");
		g_SuperAttackGaugeHandle = LoadGraph("Data/UI/BattleScene/SuperAttackGauge.png");
	}

	void DrawFrame(CharacterBase* character)
	{
		int framePosYDiff = 0;

		// フレーム
		if (character->IsBoss())
		{
			DrawRotaGraph((int)FRAME_DEFAULT_POS.x, (int)FRAME_DEFAULT_POS.y, FRAME_SCALE_OFFSET, 0.0, g_BossFrameHandle, TRUE);
		}
		else
		{
			int index = character->GetIndex();

			int bossNum = CharacterManager::GetInstance()->GetBossNum();

			if (index < bossNum)
			{
				framePosYDiff = FRAME_POS_Y_INTERVAL * (index + 1);
			}
			else
			{
				framePosYDiff = FRAME_POS_Y_INTERVAL * index;
			}

			DrawRotaGraph((int)FRAME_DEFAULT_POS.x, (int)FRAME_DEFAULT_POS.y + framePosYDiff, FRAME_SCALE_OFFSET, 0.0, g_ChallengerFrameHandle, TRUE);
		}

		// アイコン
		DrawRotaGraph(270, 40 + framePosYDiff, ICON_SCALE_OFFSET, 0.0, character->GetIconHandle(), false);
	}

	void DrawGauges(CharacterBase* character)
	{
		int index = character->GetIndex();

		int framePosYDiff = FRAME_POS_Y_INTERVAL * index;

		int hp = character->GetHP();
		int maxHp = character->GetMaxHP();

		DrawBox(50, 70 + framePosYDiff, 300, 90 + framePosYDiff, GetColor(255, 255, 255), TRUE);
		if (hp > 0)
		{
			DrawBox(50, 70 + framePosYDiff, 50 + 250 * hp / maxHp, 90 + framePosYDiff, GetColor(0, 255, 0), TRUE);
		}

		if (character->IsPlayer())
		{
			DrawCircleGauge(
				(int)UI_SKILL_POS.x, (int)UI_SKILL_POS.y,
				character->GetSkillPoint() + 50.0, g_SkillGaugeHandle, 50.0, 1.1);

			DrawCircleGauge((int)UI_SUPER_ATTACK_POS.x, (int)UI_SUPER_ATTACK_POS.y,
				character->GetSuperAttackPoint() + 50.0, g_SuperAttackGaugeHandle, 50.0, 1.1);

			DrawRotaGraph((int)UI_SKILL_POS.x, (int)UI_SKILL_POS.y, 1.0, 0.0, g_SkillHandle, TRUE);

			DrawRotaGraph((int)UI_SUPER_ATTACK_POS.x, (int)UI_SUPER_ATTACK_POS.y, 1.0, 0.0, g_SuperAttackHandle, TRUE);
		}

	}
}