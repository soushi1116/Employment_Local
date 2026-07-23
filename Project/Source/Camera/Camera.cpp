#include "Camera.h"
#include "../Character/CharacterManager.h"
#include "../Character/CharacterBase.h"
#include "../Input/Input.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionSphere.h"

const float CAMERA_NEAR_CLIP = 1.0f;
const float CAMERA_FAR_CLIP = 1000.0f;
const float PLAYER_DISTANCE = -50.0f;
const float ROTATION_SPEED = 0.03f;
const float X_ROTATION_MAX = DX_PI_F * 0.49f;
const float X_ROTATION_MIN = DX_PI_F * 0.05f;

Camera::Camera()
{
	m_TargetCharacter = nullptr;
	m_Sphere = nullptr;

	m_HitStage = false;
}

Camera::~Camera()
{
	Fin();
}

void Camera::Init()
{

}

void Camera::Load()
{

}

void Camera::Start()
{
	SetCameraNearFar(CAMERA_NEAR_CLIP, CAMERA_FAR_CLIP);

	m_UpVec = VGet(0.0f, 1.0f, 0.0f);

	CharacterBase* player = CharacterManager::GetInstance()->SearchPlayer();

	if (!player->IsBoss())
	{
		m_Rot.y = DX_PI_F;
	}
	
	m_Sphere = CollisionManager::GetInstance()->CreateSphere();
	m_Sphere->SetTargetPos(&m_Pos);
	m_Sphere->SetLocalPos(MyMath::VecZero());
	m_Sphere->SetRadius(1.0f);

	m_Rot.x = DX_PI_F * 0.2f;
}

void Camera::Step()
{
	m_HitStage = false;

	if (Input::IsInputKey(Input::KEY_A))
	{
		m_Rot.y += ROTATION_SPEED;
	}
	if (Input::IsInputKey(Input::KEY_D))
	{
		m_Rot.y -= ROTATION_SPEED;
	}
	if (Input::IsInputKey(Input::KEY_W))
	{
		m_Rot.x += ROTATION_SPEED;
	}
	if (Input::IsInputKey(Input::KEY_S))
	{
		m_Rot.x -= ROTATION_SPEED;
	}

	m_Rot.y += ROTATION_SPEED * Input::GetRightStickX() / 1000;
	m_Rot.x += ROTATION_SPEED * Input::GetRightStickY() / 1000;

	if (m_Rot.x >= X_ROTATION_MAX)
	{
		m_Rot.x = X_ROTATION_MAX;
	}
	else if (m_Rot.x <= 0.0f)
	{
		m_Rot.x = 0.0f;
	}
}

void Camera::Update()
{
	m_PrevPos = m_Pos;

	VECTOR playerPos = m_TargetCharacter->GetPos();

	if (!m_HitStage)
	{
		VECTOR vecOrigin = MyMath::VecScale(playerPos, -1.0f);
		MATRIX playerOrigin = MyMath::MatTranslation(vecOrigin);

		MATRIX distance = MyMath::MatTranslation(VGet(0.0f, 0.0f, PLAYER_DISTANCE));

		MATRIX pitch = MyMath::MatRotationPitch(m_Rot.x);
		MATRIX yaw = MyMath::MatRotationYaw(m_Rot.y);

		MATRIX matPlayerPos = MyMath::MatTranslation(playerPos);

		MATRIX cameraMat = MyMath::MatMult(matPlayerPos, yaw);
		cameraMat = MyMath::MatMult(cameraMat, pitch);
		cameraMat = MyMath::MatMult(cameraMat, distance);
		cameraMat = MyMath::MatMult(cameraMat, playerOrigin);

		m_Pos = MyMath::MatTransform(cameraMat, playerPos);
	}

	m_Target = playerPos;
	m_Target.y += m_TargetCharacter->GetRadius() * 1.5f;

	SetCameraPositionAndTargetAndUpVec(m_Pos, m_Target, m_UpVec);
}

void Camera::Draw()
{
	DrawFormatString(0, 200, GetColor(255, 255, 255), "ƒJƒƒ‰‚ÌÀ•W[%f, %f, %f]", m_Pos.x, m_Pos.y, m_Pos.z);
}

void Camera::Fin()
{
	m_Sphere = nullptr;
}

void Camera::HitStage(const MV1_COLL_RESULT_POLY_DIM* hitResult)
{
	VECTOR spherePos = m_Sphere->GetWorldPos();
	float radius = m_Sphere->GetRadius();

	bool isHitWall = false;
	float maxOverlap = 0.0f;

	for (int i = 0; i < hitResult->HitNum; i++)
	{
		const MV1_COLL_RESULT_POLY& poly = hitResult->Dim[i];

		if (fabs(poly.Normal.y) < 0.5f)
		{
			VECTOR polyToSphere = VSub(spherePos, poly.HitPosition);
			float distance = VSize(polyToSphere);

			if (distance < radius && distance > 0.0f)
			{
				isHitWall = true;
				float overlap = radius - distance;
				if (overlap > maxOverlap)
				{
					maxOverlap = overlap;
				}
			}
		}
	}

	if (isHitWall)
	{
		const float ROTATE_SPEED_FACTOTR = 0.2f;
		m_Rot.x += maxOverlap * ROTATE_SPEED_FACTOTR;
	}
}