#pragma once
#include "SceneBase.h"

class ParentSelectScene : public SceneBase
{
public:
	ParentSelectScene();
	~ParentSelectScene();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;

private:
	int m_ParentHandle;
	int m_ChildHandle;

	bool m_ParentSelected;
};