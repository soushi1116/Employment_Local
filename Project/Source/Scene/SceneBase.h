#pragma once
#include "../Sound/SoundParameter.h"
#include <vector>
#include "../Component/GameObject.h"

class UUIInput;

class SceneBase
{
public:
	SceneBase();
	~SceneBase();

public:
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start();
	virtual void Step() = 0;
	virtual void Update();
	virtual void Draw();
	virtual void Fin();

	void Instantiate(std::shared_ptr<GameObject> newObj)
	{
		m_GameObjects.push_back(newObj);
		newObj->Start();
	}

	static SceneBase* GetInstance() { return s_Instance; }

	std::vector<std::shared_ptr<GameObject>> GetGameObjects() { return m_GameObjects; }

	std::shared_ptr<GameObject> SearchGameObjectTag(Tag tag);

protected:
	bool m_SceneChangeStart;
	bool m_SceneChangeEnd;
	bool m_SceneBack;

	std::vector<std::shared_ptr<GameObject>> m_GameObjects;

	static SceneBase* s_Instance;

	std::shared_ptr<GameObject> m_UIInputObj;
	std::shared_ptr<UIInput> m_UIInputCmp;
};