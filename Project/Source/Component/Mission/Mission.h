#pragma once
#include "../Component.h"
#include <memory>

class GameObject;
class Timer;

enum MissionType
{
	KILL_OPPONENT,
	MISSION_TYPE_MAX,
	MISSION_TYPE_NONE = -1
};

enum RewardType
{
	HP_HEAL,
	POWER_UP,
	DEFENCE_UP,
	SPEED_UP,
	REWARD_TYPE_MAX,
	REWARD_TYPE_NONE = -1
};

class Mission : public Component
{
public:
	Mission(GameObject* owner);
	~Mission();

public:
	void Start() override;
	void Step() override;
	void Update() override;

public:
	void SetMissionType(MissionType type) { m_MissionType = type; }
	void SetRewardType(RewardType type) { m_RewardType = type; }

	MissionType GetMissionType() const { return m_MissionType; }
	RewardType GetRewardType() const { return m_RewardType; }

	void SetGraphObj(std::weak_ptr<GameObject> graph) { m_Graph = graph; }
	void SetIconObj(std::weak_ptr<GameObject> icon) { m_Icon = icon; }
	void SetTextObj(std::weak_ptr<GameObject> text) { m_Text = text; }
	void SetBossObj(std::weak_ptr<GameObject> boss) { m_Boss = boss; }

	void SetBordarNum(int num) { m_BordarNum = num; }

private:
	MissionType m_MissionType;
	RewardType m_RewardType;

	std::weak_ptr<Timer> m_Timer;
	std::weak_ptr<GameObject> m_Graph;
	std::weak_ptr<GameObject> m_Icon;
	std::weak_ptr<GameObject> m_Text;
	std::weak_ptr<GameObject> m_Boss;

	int m_BordarNum;
	int m_CurrnetNum;
	bool m_IsArchived;

	int m_OriginKilledNum;
};
