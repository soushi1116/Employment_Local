#include "GimmickManager.h"
#include "DxLib.h"
#include "../../Component/AllComponents.h"
#include "../../Component/GameObject.h"
#include "../../Scene/SceneManager.h"
#include <fstream>
#include <sstream>
#include <algorithm>

GimmickManager::GimmickManager()
{
	for (int i = 0; i < MAP_TYPE_MAX; i++)
	{
		m_GimmickFunc[i] = nullptr;
	}

	for (int i = 0; i < FACTORY_GIMMICK_NUM; i++)
	{
		m_GimmickData[i].m_Pos = MyMath::VecZero();
		m_GimmickData[i].m_Size = MyMath::VecZero();
	}
}

GimmickManager::~GimmickManager()
{

}

void GimmickManager::Start()
{
	m_GimmickFunc[MAP_FACTORY] = &GimmickManager::FactoryGimmick;
}

void GimmickManager::CreateGimmick(MapType type)
{
	(this->*m_GimmickFunc[type])();
}

/// <summary>
/// Factoryのギミック生成
/// </summary>
void GimmickManager::FactoryGimmick()
{
	LoadGimmickData("Data/Parameters/FactoryGimmick.csv");

	for (int i = 0; i < FACTORY_GIMMICK_NUM; i++)
	{
		auto gimmickObj = std::make_shared<GameObject>();
		gimmickObj->AddTag(TAG_GIMMICK);

		auto gimmickCmp = gimmickObj->AddComponent<Conveyor>();
		gimmickCmp->SetType(GIMMICK_TYPE_CONVEYOR);
		gimmickCmp->SetLength(max(m_GimmickData[i].m_Size.x, m_GimmickData[i].m_Size.z));
		gimmickCmp->SetDirection(m_GimmickData[i].m_Dir);

		auto gimmickPhysics = gimmickObj->AddComponent<Physics3D>();
		gimmickPhysics->SetPos(m_GimmickData[i].m_Pos);
		gimmickPhysics->SetScale(m_GimmickData[i].m_Size);

		gimmickCmp->SetPhysics(gimmickPhysics);

		auto gimmickCollision = gimmickObj->AddComponent<BoxCollision>();

		gimmickPhysics->SetCollision(gimmickCollision);

		m_Gimmicks.push_back(gimmickObj);
		SceneManager::GetInstance()->GetNowScene()->Instantiate(gimmickObj);
	}

}

/// <summary>
/// 位置・サイズデータの読み取り
/// </summary>
/// <param name="filePath">ファイル名</param>
void GimmickManager::LoadGimmickData(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open()) return;

	std::string line;
	bool isFirstLine = true;

	int rowIndex = 0;

	while (std::getline(file, line))
	{
		if (line.empty()) continue;

		// 1行目は無視
		if (isFirstLine)
		{
			isFirstLine = false;
			continue;
		}

		std::stringstream ss(line);
		std::string value;

		int columnIndex = 0;

		std::vector<float> gimmickDatas;

		while (std::getline(ss, value, ','))
		{
			float currentGimmickData = 0.0f;

			value.erase(std::remove_if(value.begin(), value.end(), ::isspace), value.end());

			// 1列目は無視
			if (columnIndex == 0)
			{
				columnIndex++;
				continue;
			}

			if (!value.empty())
			{
				try
				{
					currentGimmickData = std::stof(value);
				}
				catch (const std::invalid_argument&)
				{
					currentGimmickData = 0.0f;
				}
				catch (const std::out_of_range&)
				{
					currentGimmickData = 0.0f;
				}
			}

			gimmickDatas.push_back(currentGimmickData);
			columnIndex++;
		}

		m_GimmickData[rowIndex].m_Pos = VGet(gimmickDatas[0], gimmickDatas[1], gimmickDatas[2]);
		m_GimmickData[rowIndex].m_Size = VGet(gimmickDatas[3], gimmickDatas[4], gimmickDatas[5]);
		m_GimmickData[rowIndex].m_Dir = VGet(gimmickDatas[6], 0.0f, gimmickDatas[7]);
		
		rowIndex++;
	}
}