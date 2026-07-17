#pragma once
#include "../Sound/SoundParameter.h"

class SceneBase
{
public:
	SceneBase();
	~SceneBase();

public:
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start() = 0;
	virtual void Step();
	virtual void Update();
	virtual void Draw() = 0;
	virtual void Fin() = 0;

protected:
	int m_BGHandle;

	bool m_SceneChangeStart;
	bool m_SceneChangeEnd;

	SEType m_BButtonSEType;
};