#pragma once
#include "../Component.h"
#include <memory>

class GameObject;
class Timer;

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

	void SetBordarNum(int num) { m_BordarNum = num; }

private:
	MissionType m_MissionType;
	RewardType m_RewardType;

	struct SharedMembers
	{
		std::shared_ptr<Timer> timerShared;
		std::shared_ptr<GameObject> graphShared;
		std::shared_ptr<GameObject> iconShared;
		std::shared_ptr<GameObject> textShared;
		bool isSafety = false;
	};

	std::weak_ptr<Timer> m_Timer;
	std::weak_ptr<GameObject> m_Graph;
	std::weak_ptr<GameObject> m_Icon;
	std::weak_ptr<GameObject> m_Text;

	SharedMembers CheckMemberPtrs();

	int m_BordarNum;
	int m_CurrnetNum;
	bool m_IsArchived;
	bool m_IsOverTime;

	int m_OriginNum;
};
