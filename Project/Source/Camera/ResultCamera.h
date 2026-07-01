#pragma once
#include "DxLib.h"
#include "CameraBase.h"

class ResultCamera : public CameraBase
{
public:
	ResultCamera();
	~ResultCamera();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;

};