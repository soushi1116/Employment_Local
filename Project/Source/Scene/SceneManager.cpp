#include "SceneManager.h"
#include "BattleScene.h"
#include "TitleScene.h"
#include "HomeScene.h"
#include "ResultScene.h"
#include "ResultSceneSecond.h"
#include "MissionSelectScene.h"
#include "MapSelectScene.h"
#include "BossSelectScene.h"
#include "DebugScene.h"
#include "CharacterSelectScene.h"
#include "OptionScene.h"

SceneManager* SceneManager::m_Instance = nullptr;

SceneManager::SceneManager()
{
	m_NowScene = nullptr;
	m_State = SCENE_STATE_NONE;
	m_NextScene = SCENE_TYPE_NONE;
	m_NowSceneType = SCENE_TYPE_NONE;

	for (int i = 0; i < SCENE_STATE_MAX; i++)
	{
		m_StateFunc[i] = nullptr;
	}
}

SceneManager::~SceneManager()
{
	Fin();
}

void SceneManager::Init()
{
	m_StateFunc[INIT] = &SceneManager::InitScene;
	m_StateFunc[LOAD] = &SceneManager::LoadScene;
	m_StateFunc[START] = &SceneManager::StartScene;
	m_StateFunc[LOOP] = &SceneManager::LoopScene;
	m_StateFunc[FIN] = &SceneManager::FinScene;

	CreateScene(DEBUG);
	m_State = INIT;
}

void SceneManager::Update()
{
	while (m_State != LOOP && m_State != SCENE_STATE_NONE)
	{
		if (m_StateFunc[m_State] != nullptr)
		{
			(this->*m_StateFunc[m_State])();
		}
		else
		{
			break;
		}
	}

	if (m_State == LOOP && m_StateFunc[m_State] != nullptr)
	{
		(this->*m_StateFunc[m_State])();
	}
}

void SceneManager::Fin()
{
	if (m_NowScene)
	{
		delete m_NowScene;
	}
}

void SceneManager::ChangeScene(SceneType type)
{
	m_NextScene = type;
	m_State = FIN;
}

void SceneManager::InitScene()
{
	m_NowScene->Init();
	m_State = LOAD;
}

void SceneManager::LoadScene()
{
	m_NowScene->Load();
	m_State = START;
}

void SceneManager::StartScene()
{
	m_NowScene->Start();
	m_State = LOOP;
}

void SceneManager::LoopScene()
{
	m_NowScene->Step();
	m_NowScene->Update();
	m_NowScene->Draw();
}

void SceneManager::FinScene()
{
	m_NowScene->Fin();
	
	if (m_NowScene)
	{
		delete m_NowScene;
		m_NowScene = nullptr;
	}

	CreateScene(m_NextScene);

	m_State = INIT;
}

void SceneManager::CreateScene(SceneType type)
{
	m_NowSceneType = type;

	switch (type)
	{
	case TITLE:
		m_NowScene = new TitleScene;
		break;
	case HOME:
		m_NowScene = new HomeScene;
		break;
	case OPTION:
		m_NowScene = new OptionScene;
		break;
	case BOSS_SELECT:
		m_NowScene = new BossSelectScene;
		break;
	case CHARACTER_SELECT:
		m_NowScene = new CharacterSelectScene;
		break;
	case MAP_SELECT:
		m_NowScene = new MapSelectScene;
		break;
	case MISSION_SELECT:
		m_NowScene = new MissionSelectScene;
		break;
	case BATTLE:
		m_NowScene = new BattleScene;
		break;
	case RESULT:
		m_NowScene = new ResultScene;
		break;
	case RESULT_SECOND:
		m_NowScene = new ResultSceneSecond;
		break;
	case DEBUG:
		m_NowScene = new DebugScene;
		break;
	case SCENE_TYPE_NONE:
		break;
	default:
		break;
	}
}
