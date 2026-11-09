#include "MissionManager.h"
#include "DxLib.h"
#include "../../Component/AllComponents.h"
#include "../../Component/GameObject.h"
#include "../../Scene/SceneManager.h"
#include "../RendererManager/RendererManager.h"
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

	// 削除されるミッションがあるか
	bool isRemoved = false;

	// Missionオブジェクトが非アクティブなら削除して詰める	
	auto newEnd = std::remove_if(m_Missions.begin(), m_Missions.end(),
		[](const auto& mission) {
			for (const auto& missionObj : mission)
			{
				if (auto missionShared = missionObj.lock())
				{
					if (!missionShared->GetComponent<Mission>()) continue;

					if (!missionShared->IsActive())
					{
						return true;
					}
				}
			}

			return false;
		});

	if (newEnd != m_Missions.end())
	{
		isRemoved = true;
		m_Missions.erase(newEnd, m_Missions.end());
	}

	// 削除されたミッションがあれば位置を詰める
	if (isRemoved)
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

				if (!spriteRenderer && !textRenderer) continue;

				float posYOffset = MISSION_POS_Y_INTERVAL * i;

				VECTOR graphPos = VAdd(MISSION_DEFAULT_POS, MyMath::VecY(posYOffset));
				VECTOR textPos = VAdd(graphPos, MISSION_TEXT_POS_OFFSET);

				if (spriteRenderer) spriteRenderer->SetPos(graphPos);
				if (textRenderer) textRenderer->SetPos(textPos);
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
	missionTimer->CountStart(10);

	missionObjs.push_back(mission);

	const char* graphPath = "";

	switch (missionType)
	{
	case KILL_OPPONENT:
		graphPath = "Data/UI/Mission/KillOpponent.png";
		break;
	case MISSION_TYPE_MAX:
		break;
	case MISSION_TYPE_NONE:
		break;
	default:
		break;
	}

	SceneBase* nowScene = SceneManager::GetInstance()->GetNowScene();

	RendererManager* rendererManager = RendererManager::GetInstance();

	float posYOffset = MISSION_POS_Y_INTERVAL * m_Missions.size();

	VECTOR graphPos = VAdd(MISSION_DEFAULT_POS, MyMath::VecY(posYOffset));

	std::shared_ptr<GameObject> missionImage = rendererManager->CreateUIImage(graphPath, graphPos, VGet(0.7f, 0.7f, 1.0f), 0.0f);

	missionObjs.push_back(missionImage);

	missionCmp->SetGraphObj(missionImage);

	VECTOR textPos = VAdd(graphPos, MISSION_TEXT_POS_OFFSET);

	std::shared_ptr<GameObject> numTextObj = rendererManager->CreateUIText(textPos, COLOR_BLACK, NAME_BATTLE_SCENE, "0 / 0");

	missionObjs.push_back(numTextObj);

	missionCmp->SetTextObj(numTextObj);

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