#pragma once
#include "SceneBase.h"
#include "SceneParameter.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new SceneManager;
		}
	}

	static SceneManager* GetInstance() { return m_Instance; }

	static void DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

public:
	void Init();
	void Update();
	void Fin();

	void ChangeScene(SceneType type);

public:
	SceneType GetNowScene() { return m_NowSceneType; }

private:
	void InitScene();
	void LoadScene();
	void StartScene();
	void LoopScene();
	void FinScene();

	void CreateScene(SceneType type);

private:
	static SceneManager* m_Instance;

	SceneBase* m_NowScene;

	SceneState m_State;

	SceneType m_NowSceneType;
	SceneType m_NextScene;

	void (SceneManager::* m_StateFunc[SCENE_STATE_MAX])(void);
};