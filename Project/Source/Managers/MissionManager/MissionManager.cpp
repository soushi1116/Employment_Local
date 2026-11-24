#include "MissionManager.h"
#include "DxLib.h"
#include "../../Component/AllComponents.h"
#include "../../Component/GameObject.h"
#include "../../Scene/SceneManager.h"
#include "../RendererManager/RendererManager.h"
#include "../CharacterManager/CharacterManager.h"
#include "../../MyColor/MyColor.h"
#include <algorithm>

MissionManager::MissionManager()
{

}

MissionManager::~MissionManager()
{

}

void MissionManager::Update()
{
	if (m_Missions.empty()) return;

	// 削除されるミッションの数
	int removedNum = 0;

	// Missionオブジェクトが非アクティブなら削除して詰める	
	auto newEnd = std::remove_if(m_Missions.begin(), m_Missions.end(),
		[&removedNum](const auto& mission) {
			for (const auto& missionObj : mission)
			{
				if (auto missionShared = missionObj.lock())
				{
					if (!missionShared->GetComponent<Mission>()) continue;

					if (!missionShared->IsActive())
					{
						removedNum++;
						return true;
					}
				}
			}

			return false;
		});

	if (newEnd != m_Missions.end())
	{
		m_Missions.erase(newEnd, m_Missions.end());
	}

	if (removedNum <= 0) return;

	// 削除されたミッションの数だけ位置を詰める
	for (int n = 0; n < removedNum; n++)
	{
		for (int i = 0; i < m_Missions.size(); i++)
		{
			const auto& missionUI = m_Missions[i];

			for (int j = 0; j < missionUI.size(); j++)
			{
				const auto& uiObject = missionUI[j].lock();

				if (!uiObject) continue;

				const auto& spriteRenderer = uiObject->GetComponent<SpriteRenderer>();
				const auto& textRenderer = uiObject->GetComponent<TextRenderer>();

				VECTOR currentPos, newPos = MyMath::VecZero();

				float posYDelta = -MISSION_POS_Y_INTERVAL;

				if (spriteRenderer)
				{
					currentPos = spriteRenderer->GetPos();
					newPos = VAdd(currentPos, MyMath::VecY(posYDelta));
					spriteRenderer->SetPos(newPos);
				}
				else if (textRenderer)
				{
					currentPos = textRenderer->GetPos();
					newPos = VAdd(currentPos, MyMath::VecY(posYDelta));
					textRenderer->SetPos(newPos);
				}
				else continue;
			}
		}
	}
}

std::vector<std::shared_ptr<GameObject>> MissionManager::CreateMission()
{
	std::vector<std::shared_ptr<GameObject>> missionObjs;
	
	MissionType missionType = static_cast<MissionType>(GetRand(MISSION_TYPE_MAX - 1));
	RewardType rewardType = static_cast<RewardType>(GetRand(REWARD_TYPE_MAX - 1));

	auto mission = std::make_shared<GameObject>();

	auto missionCmp = mission->AddComponent<Mission>();
	missionCmp->SetMissionType(missionType);
	missionCmp->SetRewardType(rewardType);

	auto missionTimer = mission->AddComponent<Timer>();
	missionTimer->CountStart(15);

	missionObjs.push_back(mission);

	// ミッションの画像ロード
	const char* graphPath = "";

	switch (missionType)
	{
	case DAMAGE:
		graphPath = "Data/UI/Mission/Damage.png";
		missionCmp->SetBordarNum(100);
		break;
	case MISSION_TYPE_MAX:
		break;
	case MISSION_TYPE_NONE:
		break;
	default:
		break;
	}

	// 報酬のアイコン画像ロード
	const char* iconPath = "";

	switch (rewardType)
	{
	case HP_HEAL:
		iconPath = "Data/UI/BattleScene/HealIcon.png";
		break;
	case POWER_UP:
		iconPath = "Data/UI/BattleScene/PowerUpIcon.png";
		break;
	case DEFENCE_UP:
		iconPath = "Data/UI/BattleScene/DefenceUpIcon.png";
		break;
	case SPEED_UP:
		iconPath = "Data/UI/BattleScene/SpeedUpIcon.png";
		break;
	case REWARD_TYPE_MAX:
		break;
	case REWARD_TYPE_NONE:
		break;
	default:
		break;
	}

	RendererManager* rendererManager = RendererManager::GetInstance();

	// 既存のミッションの数だけ位置補正
	float posYOffset = MISSION_POS_Y_INTERVAL * m_Missions.size();

	// ミッションの画像生成
	VECTOR graphPos = VAdd(MISSION_DEFAULT_POS, MyMath::VecY(posYOffset));

	std::shared_ptr<GameObject> missionImage = rendererManager->CreateUIImage(graphPath, graphPos, VGet(MISSION_GRAPH_SIZE_OFFSET, MISSION_GRAPH_SIZE_OFFSET, 1.0f), 0.0f);

	missionObjs.push_back(missionImage);

	missionCmp->SetGraphObj(missionImage);

	// 報酬のアイコン画像生成
	VECTOR iconPos = VAdd(graphPos, MISSION_ICON_POS_OFFSET);

	std::shared_ptr<GameObject> iconImage = rendererManager->CreateUIImage(iconPath, iconPos, VGet(MISSION_ICON_SIZE_OFFSET, MISSION_ICON_SIZE_OFFSET, 1.0f), 0.0f);

	missionObjs.push_back(iconImage);

	missionCmp->SetIconObj(iconImage);

	// 達成状況のテキスト生成
	VECTOR textPos = VAdd(graphPos, MISSION_TEXT_POS_OFFSET);

	std::shared_ptr<GameObject> numTextObj = rendererManager->CreateUIText(textPos, COLOR_BLACK, MISSION_TEXT, "0 / 0");

	missionObjs.push_back(numTextObj);

	missionCmp->SetTextObj(numTextObj);


	SceneBase* nowScene = SceneManager::GetInstance()->GetNowScene();
	for (auto& ui : missionObjs)
	{
		nowScene->Instantiate(ui);
	}

	m_Missions.emplace_back();

	auto& missionWeakVector = m_Missions.back();

	for (const auto& uiShared : missionObjs)
	{
		missionWeakVector.push_back(uiShared);
	}

	return missionObjs;
}