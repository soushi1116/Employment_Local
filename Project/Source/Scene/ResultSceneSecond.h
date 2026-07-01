#pragma once
#include "SceneBase.h"

class ResultSceneSecond : public SceneBase
{
public:
	ResultSceneSecond();
	~ResultSceneSecond();

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