#pragma once
#include "DxLib.h"
#include "CameraBase.h"

class CharacterBase;

class Camera : public CameraBase
{
public:
	Camera();
	~Camera();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;


};