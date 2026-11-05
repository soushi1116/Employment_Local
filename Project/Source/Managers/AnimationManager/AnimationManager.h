#pragma once
#include <vector>
#include <string>
#include "../../Component/Animation/Animation.h"
#include "../../Component/Character/CharacterParameter.h"
#include "../Singleton.h"

class AnimationManager : public Singleton<AnimationManager>
{
public:
	AnimationManager();
	~AnimationManager();

public:
	bool LoadAnimationData(const std::string& filePath);
	float GetTotalTime(CharacterType characterType, CharacterAnimationType animType);

private:
	static AnimationManager* m_Instance;
	std::vector<std::vector<float>> m_TotalTimeTable;
};

