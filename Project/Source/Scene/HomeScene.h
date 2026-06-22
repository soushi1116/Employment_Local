#pragma once
#include "SceneBase.h"

class HomeScene : public SceneBase
{
public:
	HomeScene();
	~HomeScene();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;

private:
};