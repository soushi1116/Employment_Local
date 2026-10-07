#pragma once
#include <vector>
#include <string>
#include "../../Component/Animation/Animation.h"
#include "../../Component/Character/CharacterParameter.h"

class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new AnimationManager;
		}
	}

	static AnimationManager* GetInstance() { return m_Instance; }

	static void DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

public:
	bool LoadAnimationData(const std::string& filePath);
	float GetTotalTime(CharacterType characterType, CharacterAnimationType animType);

private:
	static AnimationManager* m_Instance;
	std::vector<std::vector<float>> m_TotalTimeTable;
};

