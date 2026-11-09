#pragma once
#include "DxLib.h"
#include <vector>
#include <list>
#include <string>
#include <memory>
#include "../Singleton.h"
#include "../../MyMath/MyMath.h"

const VECTOR MISSION_DEFAULT_POS = MyMath::Vec2D(1300.0f, 100.0f);
const VECTOR MISSION_TEXT_POS_OFFSET = MyMath::Vec2D(100.0f, -20.0f);
const float MISSION_POS_Y_INTERVAL = 100.0f;

class GameObject;
class Mission;

class MissionManager : public Singleton<MissionManager>
{
public:
	MissionManager();
	~MissionManager();

	void Update();

public:
	std::vector<std::shared_ptr<GameObject>> CreateMission();

private:
	static MissionManager* m_Instance;

	std::vector<std::vector<std::weak_ptr<GameObject>>> m_Missions;
};