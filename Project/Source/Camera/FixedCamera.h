#pragma once
#include "DxLib.h"
#include "CameraBase.h"

class FixedCamera : public CameraBase
{
public:
	FixedCamera();
	~FixedCamera();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;

	void HitStage(const MV1_COLL_RESULT_POLY_DIM* hitResult) override;
};