#pragma once
#include "Dxlib.h"
#include <vector>
#include "EffekseerParameter.h"

class EffekseerEffect;

class EffekseerManager
{
public:
	EffekseerManager();
	~EffekseerManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new EffekseerManager;
		}
	}

	static EffekseerManager* GetInstance() { return m_Instance; }

	static void DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

public:
	void SetUp();
	bool Init();
	void Load();
	void Start();

	EffekseerEffect* PlayEffect(EffekseerEffectType type, VECTOR pos);

	void Step();
	void Update();
	void Draw();
	void Fin();

private:
	static EffekseerManager* m_Instance;

	std::vector<int> m_EffectHandles;
	std::vector<EffekseerEffect*> m_Effects;
};

