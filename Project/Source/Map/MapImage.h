#pragma once
#include "DxLib.h"
#include "../Managers/CharacterManager/CharacterManager.h"

class MapImage
{
public:
	MapImage();
	~MapImage();

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

public:
	void SetScale(VECTOR scale) { m_MapScale = scale; }

private:
	int m_Handle;
	int m_CharacterIndex;

	VECTOR m_CharacterPos[CHARACTER_MAX_NUM];
	VECTOR m_ImageScale;
	VECTOR m_MapScale;
};
