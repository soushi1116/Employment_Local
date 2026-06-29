#pragma once
#include "SceneBase.h"

class ResultScene : public SceneBase
{
public:
	ResultScene();
	~ResultScene();

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