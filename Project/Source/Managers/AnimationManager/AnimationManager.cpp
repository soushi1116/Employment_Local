#include "AnimationManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>

AnimationManager* AnimationManager::m_Instance = nullptr;

AnimationManager::AnimationManager()
{

}

AnimationManager::~AnimationManager()
{

}

bool AnimationManager::LoadAnimationData(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open()) return false;

	m_TotalTimeTable.clear();
	std::string line;
	bool isFirstLine = true;

	while (std::getline(file, line))
	{
		if (line.empty()) continue;

		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		std::vector<float> characterRaw;
		std::stringstream ss(line);
		std::string value;

		while (std::getline(ss, value, ','))
		{
			value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());

			if (value.empty())
			{
				characterRaw.push_back(0.0f);
			}
			else
			{
				characterRaw.push_back(std::stof(value));
			}
		}

		if (characterRaw.empty())
		{
			m_TotalTimeTable.push_back(characterRaw);
		}
	}
	return true;
}

float AnimationManager::GetTotalTime(int characterID, CharacterAnimationType type)
{
	int animIndex = static_cast<int>(type);

	if (characterID < 0 || characterID >= (int)m_TotalTimeTable.size()) return 0.0f;
	if (animIndex < 0 || animIndex >= (int)m_TotalTimeTable[characterID].size()) return 0.0f;

	return m_TotalTimeTable[characterID][animIndex];
}
