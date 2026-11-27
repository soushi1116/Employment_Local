#pragma once
#include "DxLib.h"
#include <vector>
#include <memory>
#include <string>
#include "../Singleton.h"
#include "../../MyEnums/MyEnums.h"

constexpr int FACTORY_GIMMICK_NUM = 4;

class GameObject;
class GimmickBase;

class GimmickManager : public Singleton<GimmickManager>
{
public:
	GimmickManager();
	~GimmickManager();

public:
	void Start();

public:
	void CreateGimmick(MapType type);

	void FactoryGimmick();

private:
	void LoadGimmickData(const std::string& filePath);

private:
	static GimmickManager* m_Instance;

	std::vector<std::weak_ptr<GameObject>> m_Gimmicks;

	void (GimmickManager::* m_GimmickFunc[MAP_TYPE_MAX])(void);

	struct GimmickSpawnData
	{
		VECTOR m_Pos; 
		VECTOR m_Size;
		VECTOR m_Dir;
	};

	GimmickSpawnData m_GimmickData[FACTORY_GIMMICK_NUM];
};