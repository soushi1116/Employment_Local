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

		int columnIndex = 0;
		std::string characterName = "";

		while (std::getline(ss, value, ','))
		{
			value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());

			if (columnIndex == 0)
			{
				characterName = value;
				columnIndex++;
				continue;
			}

			if (value.empty())
			{
				characterRaw.push_back(0.0f);
			}
			else
			{
				try
				{
					characterRaw.push_back(std::stof(value));
				}
				catch (const std::invalid_argument& e)
				{
					characterRaw.push_back(0.0f);
				}
				
			}

			columnIndex++;
		}

		if (!characterRaw.empty())
		{
			m_TotalTimeTable.push_back(characterRaw);
		}
	}
	return true;
}

float AnimationManager::GetTotalTime(CharacterType characterType, CharacterAnimationType animType)
{
	int characterIndex = static_cast<int>(characterType);
	int animIndex = static_cast<int>(animType);

	if (characterIndex < 0 || characterIndex >= (int)m_TotalTimeTable.size()) return 0.0f;
	if (animIndex < 0 || animIndex >= (int)m_TotalTimeTable[characterIndex].size()) return 0.0f;

	return m_TotalTimeTable[characterIndex][animIndex];
}
