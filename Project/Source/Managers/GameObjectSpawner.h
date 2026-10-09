#pragma once

class GameObjectSpawner
{
public:
	GameObjectSpawner();
	~GameObjectSpawner();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new GameObjectSpawner;
		}
	}

	static GameObjectSpawner* GetInstance() { return m_Instance; }

	static void DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}


	void SpawnGameObject();

private:
	static GameObjectSpawner* m_Instance;
};