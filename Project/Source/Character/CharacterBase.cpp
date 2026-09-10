#define NOMINMAX
#include "CharacterBase.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../Map/MapManager.h"
#include "../Map/MapBase.h"
#include "../Item/ItemManager.h"
#include "../Item/ItemBase.h"
#include "../MyEffekseer/EffekseerManager.h"
#include "../BattleManager/BattleManager.h"
#include "../Input/Input.h"
#include "../Camera/CameraManager.h"
#include "CharacterManager.h"
#include "../Bullet/BulletManager.h"
#include "../FPS/FPSManager.h"
#include "../Scene/SceneManager.h"
#include "../UI/UIManager.h"
#include "Rooter/Rooter.h"
#include <algorithm>

const int RESPAWN_INTERVAL = 180;

const float ANIMATION_SPEED = 1.0f;
const float GRAVITY = 0.01f;
const float BLEND_DURATION = 0.2f;
const float OBSTACLE_SEARCH_LENGTH = 20.0f;

const VECTOR PARENT_DEFAULT_POS = VGet(0.0f, 0.0f, -100.0f);
const VECTOR CHILD_DEFAULT_POS = VGet(40.0f, 0.0f, 120.0f);

const VECTOR UI_SKILL_POS = VGet(175.0f, 775.0f, 0.0f);
const VECTOR UI_SUPER_ATTACK_POS = VGet(475.0f, 775.0f, 0.0f);
const float UI_SKILL_AND_SUPER_ATTACK_RADIUS = 75.0f;
const int UI_NAME_SCALE = 42;

const int UI_ICON_POS_DIFF = 150;
const int DIRECTION_CHANGE_INTERVAL = 10;
const int ROOTER_CREATE_INTERVAL = 5 * 60;
const VECTOR FRAME_DEFAULT_START_POS = MyMath::Vec2D(40.0f, 10.0f);
const VECTOR FRAME_DEFAULT_END_POS = MyMath::Vec2D(310.0f, 100.0f);

CharacterBase::CharacterBase()
{
	m_Pos = MyMath::VecZero();
	m_PrevPos = MyMath::VecZero();
	m_Rot = MyMath::VecZero();
	m_Scale = MyMath::VecZero();
	m_Move = MyMath::VecZero();
	m_DefaultPos = MyMath::VecZero();
	m_MoveDir = MyMath::VecZero();
	m_Active = false;
	m_Randing = false;
	m_AttackHitFlag = false;
	m_Dead = false;
	m_IsBoss = false;
	m_InBattleScene = false;
	m_IsPlayer = false;
	m_Invisible = false;
	m_AvoidRight = false;
	m_Power = 0;
	m_Speed = 0.0f;
	m_Radius = 0.0f;
	m_AttackRange = 0.0f;
	m_SuperAttackRange = 0.0f;
	m_PowerMagni = 0.0f;
	m_DefenceMagni = 0.0f;
	m_Hp = 0;
	m_MaxHp = 0;
	m_RespawnTimer = 0;
	m_Index = 0;
	m_SkillPoint = 0;
	m_SuperAttackPoint = 0;
	m_KilledNum = 0;
	m_SkillPointSpend = 0;
	m_SuperAttackPointSpend = 0;
	m_FramePosYOffset = 0;
	m_Gravity = 0.0f;
	m_Type = CHARACTER_TYPE_NONE;
	m_ActionType = ACTION_TYPE_NONE;
	m_AABB = nullptr;
	m_Sphere = nullptr;
	
	m_AnimationAttachIndex = -1;
	m_PrevAnimationAttachIndex = -1;
	m_BlendTime = 0.0f;
	m_AnimationTotalTime = 0.0f;
	m_AnimationNowTime = 0.0f;
	m_IsLoopAnimation = false;
	m_NowAnimation = ANIMATION_STOP;
	m_Target = nullptr;

	// ハンドル
	m_Handle = 0;
	m_IconHandle = 0;
	m_FrameHandle = 0;

	for (int i = 0; i < ANIMATION_MAX; i++)
	{
		m_AnimTotalTimes[i] = 0.0f;
	}

	m_SkillFlag = false;
	m_SuperAttackFlag = false;
	m_DirectionChangeTimer = 0;
	m_RooterCreateTimer = 0;

	m_SkillGaugeHandle = 0;
	m_SuperAttackGaugeHandle = 0;
}

CharacterBase::~CharacterBase()
{
	Fin();
}

void CharacterBase::Init()
{
	m_IsBoss = false;
}

void CharacterBase::Load()
{
	if (m_IsPlayer)
	{
		m_SkillGaugeHandle = LoadGraph("Data/UI/BattleScene/SkillGauge.png");
		m_SuperAttackGaugeHandle = LoadGraph("Data/UI/BattleScene/SuperAttackGauge.png");

		UIManager* uiManager = UIManager::GetInstance();
		uiManager->CreateUIImage(UI_SKILL, UI_SKILL_POS);
		uiManager->CreateUIImage(UI_SUPER_ATTACK, UI_SUPER_ATTACK_POS);
	}

	if (m_IsBoss)
	{
		m_FrameHandle = LoadGraph("Data/UI/BattleScene/BossFrame.png");
	}
	else
	{
		m_FrameHandle = LoadGraph("Data/UI/BattleScene/BasterFrame.png");
	}
}

void CharacterBase::Start()
{
	m_DirectionChangeTimer = DIRECTION_CHANGE_INTERVAL;
	m_RooterCreateTimer = 0;

	m_PowerMagni = 1.0f;
	m_DefenceMagni = 1.0f;

	int bossNum = CharacterManager::GetInstance()->GetBossNum();

	if (m_IsBoss)
	{
		m_FramePosYOffset = 0;
	}
	else
	{
		if (m_Index < bossNum)
		{
			m_FramePosYOffset = (m_Index + 1) * UI_ICON_POS_DIFF;
		}
		else
		{
			m_FramePosYOffset = m_Index * UI_ICON_POS_DIFF;
		}
	}

	m_Scale = VGet(10.0f, 10.0f, 10.0f);

	m_DefaultPos = m_Pos;

	unsigned int nameTextColor = GetColor(0, 0, 0);

	if (m_IsBoss)
	{
		nameTextColor = GetColor(255, 255, 255);
	}

	UIManager::GetInstance()->CreateUIText(m_Name.c_str(), VGet(50.0f, 20.0f + m_FramePosYOffset, 0.0f), nameTextColor, UI_NAME_SCALE);
}

void CharacterBase::Step()
{
	m_Move = VGet(0.0f, 0.0f, 0.0f);

	if (!m_InBattleScene)
	{
		PlayAnimation(ANIMATION_STOP, true);
		return;
	}

	if (m_IsPlayer)
	{
		PlayerMove();
	}
	else
	{
		CPUMove();
	}

	if (m_Randing)
	{
		m_Gravity = 0.0f;

		m_Move.y = -0.0001f;
	}
	else
	{
		m_Gravity -= GRAVITY;

		m_Move.y = m_Gravity;
	}

	if (m_ActionType == ACTION_TYPE_NONE)
	{
		if (m_Move.x == 0.0f && m_Move.z == 0.0f)
		{
			PlayAnimation(ANIMATION_STOP, true);
		}
		else
		{
			if (MyMath::VecLong(m_Move) < m_Speed / 1.5f)
			{
				PlayAnimation(ANIMATION_WALK, true);
			}
			else
			{
				PlayAnimation(ANIMATION_RUN, true);
			}
			m_Rot.y = atan2f(m_Move.x, m_Move.z);
		}
	}

	for (auto& state : m_StateList)
	{
		if (state == STATE_POISONED)
		{
			FPSSystem* fps = FPSManager::GetInstance()->GetFPS();
			if (fps->TakeOneSecond())
			{
				Poison();
			}
			continue;
		}
	}

	m_Randing = false;

	UpdateAnimation();

	/*MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);*/

	DxLib::MV1RefreshCollInfo(m_Handle, -1);
}

void CharacterBase::PlayerMove()
{
	if (!m_Dead)
	{
		if (m_ActionType == ACTION_TYPE_NONE)
		{
			CameraBase* camera = CameraManager::GetInstance()->GetCamera(CAMERA);
			float cameraRotY = camera->GetRot().y;

			VECTOR frontVec = VGet(sinf(cameraRotY), 0.0f, cosf(cameraRotY));
			VECTOR rightVec = VGet(cosf(cameraRotY), 0.0f, -sinf(cameraRotY));

			float stickX = (float)Input::GetLeftStickX() / 1000.0f;
			float stickY = (float)Input::GetLeftStickY() / 1000.0f;

			m_Move = MyMath::VecAdd(MyMath::VecScale(frontVec, -stickY), MyMath::VecScale(rightVec, stickX));

			m_Move = MyMath::VecScale(m_Move, m_Speed);			
		}

		if (Input::IsTriggerButton(Input::BUTTON_RB))
		{
			if (m_ActionType == ACTION_TYPE_NONE)
			{
				Attack();
			}
		}

		if (Input::IsTriggerButton(Input::BUTTON_B))
		{
			if (m_ActionType == ACTION_TYPE_NONE)
			{
				Skill();
			}
		}

		if (Input::IsTriggerButton(Input::BUTTON_LB))
		{
			if (m_ActionType == ACTION_TYPE_NONE)
			{
				SuperAttack();
			}
		}
	}

	if (m_Rot.y < 0)
	{
		m_Rot.y += DX_TWO_PI_F;
	}
	else if (m_Rot.y > DX_TWO_PI_F)
	{
		m_Rot.y -= DX_TWO_PI_F;
	}
}

void CharacterBase::CPUMove()
{
	if (!m_Dead)
	{
		const auto& characterList = CharacterManager::GetInstance()->GetCharacterList();

		float minDistanceSq = FLT_MAX;

		VECTOR targetPos = MyMath::VecZero();

		// ターゲット決定
		FPSSystem* fps = FPSManager::GetInstance()->GetFPS();
		if (fps->TakeOneSecond())
		{
			if (m_IsBoss)
			{
				for (auto character : characterList)
				{
					if (character->IsBoss()) continue;
					if (character->IsDead()) continue;

					VECTOR cPos = character->GetPos();
					float diffX = cPos.x - m_Pos.x;
					float diffY = cPos.y - m_Pos.y;
					float diffZ = cPos.z - m_Pos.z;

					float currentDistanceSq = diffX * diffX + diffY * diffY + diffZ * diffZ;

					if (currentDistanceSq < minDistanceSq)
					{
						minDistanceSq = currentDistanceSq;
						m_Target = character;
					}
				}
			}
			else
			{
				for (auto character : characterList)
				{
					if (character->IsBoss())
					{
						m_Target = character;

						break;
					}
				}
			}
		}

		if (m_Target != nullptr)
		{
			m_RooterCreateTimer--;

			if (m_RooterCreateTimer <= 0)
			{
				CharacterManager::GetInstance()->CreateRooter(this, m_Target);
				m_RooterCreateTimer = ROOTER_CREATE_INTERVAL;
			}

			targetPos = m_Target->GetPos();
		}

		// 移動
		VECTOR toTarget = MyMath::VecZero();

		if (m_Target != nullptr)
		{
			m_DirectionChangeTimer--;

			VECTOR obstacleNormal = MyMath::VecZero();
			bool hitObstacle = false;

			toTarget = MyMath::VecCreate(m_Pos, targetPos);

			if (m_DirectionChangeTimer <= 0)
			{
				// 自身の右端と左端から前方に向けて障害物検知（引っかかりを防ぐ）
				MV1_COLL_RESULT_POLY_DIM checkObstacleRight = CheckObstacleForward(true);
				MV1_COLL_RESULT_POLY_DIM checkObstacleLeft = CheckObstacleForward(false);

				// 右端からの判定
				if (checkObstacleRight.HitNum > 0)
				{
					for (int i = 0; i < checkObstacleRight.HitNum; i++)
					{
						if (checkObstacleRight.Dim[i].Normal.y < 0.7f)
						{
							MV1_COLL_RESULT_POLY* poly = &checkObstacleRight.Dim[i];

							if (poly != nullptr)
							{
								obstacleNormal = poly->Normal;
								hitObstacle = true;
								break;
							}
						}
					}
				}
				// 左端からの判定
				else if (checkObstacleLeft.HitNum > 0)
				{
					for (int i = 0; i < checkObstacleLeft.HitNum; i++)
					{
						if (checkObstacleLeft.Dim[i].Normal.y < 0.7f)
						{
							MV1_COLL_RESULT_POLY* poly = &checkObstacleLeft.Dim[i];

							if (poly != nullptr)
							{
								obstacleNormal = poly->Normal;
								hitObstacle = true;
								break;
							}
						}
					}
				}

				MV1CollResultPolyDimTerminate(checkObstacleRight);
				MV1CollResultPolyDimTerminate(checkObstacleLeft);

				// 障害物があれば迂回
				if (hitObstacle)
				{
					m_DirectionChangeTimer = DIRECTION_CHANGE_INTERVAL;

					if (m_AvoidRight)
					{
						m_MoveDir = VCross(obstacleNormal, MyMath::VecY(1.0f));
					}
					else
					{
						m_MoveDir = VCross(obstacleNormal, MyMath::VecY(-1.0f));
					}
				}
				else
				{
					m_MoveDir = toTarget;
				}
			}			
		}

		float targetDistance = MyMath::VecLong(toTarget);

		VECTOR moveDirNormal = MyMath::VecNormarize(m_MoveDir);

		if (m_Target != nullptr && m_ActionType == ACTION_TYPE_NONE)
		{
			m_Rot.y = atan2f(moveDirNormal.x, moveDirNormal.z);

			// 攻撃の射程範囲内であれば攻撃、範囲外であれば移動
			if (targetDistance >= m_AttackRange)
			{
				m_Move.x = m_Speed * moveDirNormal.x;
				m_Move.z = m_Speed * moveDirNormal.z;
			}
			else
			{
				m_Move.x = 0.0f;
				m_Move.z = 0.0f;
				Attack();
			}

			// 必殺技の射程範囲内かつ必殺技フラグが立っていれば必殺技使用
			if (m_SuperAttackFlag && targetDistance < m_SuperAttackRange)
			{
				SuperAttack();
			}
		}

		// スキル使用フラグが立っていればスキル使用
		if (m_SkillFlag)
		{
			Skill();
		}
	}
}

void CharacterBase::Update()
{
	if (m_InBattleScene)
	{
		m_PrevPos = m_Pos;

		m_Pos.x += m_Move.x;
		m_Pos.y += m_Move.y;
		m_Pos.z += m_Move.z;

		if (m_Pos.y < -50.0f)
		{
			Respawn(m_DefaultPos);
		}

		if (m_Hp <= 0)
		{
			m_RespawnTimer++;

			if (m_RespawnTimer > RESPAWN_INTERVAL)
			{
				Respawn(m_DefaultPos);
				m_RespawnTimer = 0;
			}
		}

		SceneType nowScene = SceneManager::GetInstance()->GetNowScene();

		if (nowScene != DEBUG)
		{
			if (CheckHitCoin())
			{
				if (m_SuperAttackPoint <= 100)
				{
					m_SuperAttackPoint++;
				}
			}
		}

		if (m_IsBoss)
		{
			if (m_Move.x != 0.0f || m_Move.z != 0.0f)
			{
				BattleManager::GetInstance()->ResetNoMoveTimer();
			}
		}
	}

	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1SetScale(m_Handle, m_Scale);
}

void CharacterBase::DrawModel()
{	
	if (m_Invisible)
	{
		MV1SetOpacityRate(m_Handle, 0.5f);
	}
	else
	{
		MV1SetOpacityRate(m_Handle, 1.0f);
	}

	MV1DrawModel(m_Handle);
}

void CharacterBase::DrawUI()
{
	// フレーム
	if (m_IsBoss)
	{
		DrawGraph((int)FRAME_DEFAULT_START_POS.x, (int)FRAME_DEFAULT_START_POS.y, m_FrameHandle, TRUE);
	}
	else
	{
		int bossNum = CharacterManager::GetInstance()->GetBossNum();

		if (m_Index < bossNum)
		{
			DrawGraph((int)FRAME_DEFAULT_START_POS.x, (int)FRAME_DEFAULT_START_POS.y + m_FramePosYOffset, m_FrameHandle, TRUE);
		}
		else
		{
			DrawGraph((int)FRAME_DEFAULT_START_POS.x, (int)FRAME_DEFAULT_START_POS.y + m_FramePosYOffset, m_FrameHandle, TRUE);
		}
	}

	// HPゲージ
	DrawBox(50, 70 + m_FramePosYOffset, 300, 90 + m_FramePosYOffset, GetColor(255, 255, 255), TRUE);
	if (m_Hp > 0)
	{
		DrawBox(50, 70 + m_FramePosYOffset, 50 + 250 * m_Hp / m_MaxHp, 90 + m_FramePosYOffset, GetColor(0, 255, 0), TRUE);
	}

	// アイコン
	DrawRotaGraph(270, 40 + m_FramePosYOffset, 0.4, 0.0, m_IconHandle, false);

	if (m_IsPlayer)
	{
		DrawCircleGauge(
			(int)UI_SKILL_POS.x, (int)UI_SKILL_POS.y,
			m_SkillPoint + 50.0, m_SkillGaugeHandle, 50.0, 1.1);

		DrawCircleGauge((int)UI_SUPER_ATTACK_POS.x, (int)UI_SUPER_ATTACK_POS.y,
			m_SuperAttackPoint + 50.0, m_SuperAttackGaugeHandle, 50.0, 1.1);
	}

	// 状態表示
	auto stateIconList = CharacterManager::GetInstance()->GetStateIconList();

	int index = 0;

	for (auto& state : m_StateList)
	{
		switch (state)
		{
		case STATE_POWER_UP:
			DrawRotaGraph(350 + index * 50, 50 + m_FramePosYOffset, 0.6, 0.0, stateIconList[state], TRUE);
			break;
		case STATE_DEFENCE_UP:
			DrawRotaGraph(350 + index * 50, 50 + m_FramePosYOffset, 0.6, 0.0, stateIconList[state], TRUE);
			break;
		case STATE_POISONED:
			DrawRotaGraph(350 + index * 50, 50 + m_FramePosYOffset, 0.6, 0.0, stateIconList[state], TRUE);
			break;
		case STATE_TYPE_MAX:
			break;
		case STATE_TYPE_NONE:
			break;
		default:
			break;
		}

		index++;
	}

	if (m_IsPlayer)
	{
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%f", m_DefenceMagni);
	}
}

void CharacterBase::Fin()
{
	for (int i = 0; i < ANIMATION_MAX; i++)
	{
		MV1DeleteModel(m_Handle);
	}
	
	m_AABB = nullptr;
	m_Sphere = nullptr;

	DeleteGraph(m_SkillGaugeHandle);
	DeleteGraph(m_SuperAttackGaugeHandle);

}

void CharacterBase::Respawn(VECTOR pos)
{
	m_ActionType = ACTION_TYPE_NONE;

	PlayAnimation(ANIMATION_STOP, true);

	m_Pos = pos;
	m_Hp = m_MaxHp;
	m_SkillPoint = 0;
	m_SuperAttackPoint = 0;
	m_Dead = false;
	if (m_Sphere != nullptr)
	{
		m_Sphere->SetTargetPos(&m_Pos);
	}
}

void CharacterBase::Attack()
{
	PlayAnimation(ANIMATION_ATTACK, false);
	m_ActionType = ACTION_ATTACK;

	ClearHitVictimList();
}

void CharacterBase::Skill()
{
	if (m_SkillPoint > m_SkillPointSpend)
	{
		PlayAnimation(ANIMATION_SKILL, false);
		m_ActionType = ACTION_SKILL;

		m_SkillPoint -= m_SkillPointSpend;

		m_SkillFlag = false;
	}
}

void CharacterBase::SuperAttack()
{
	if (m_SuperAttackPoint > m_SuperAttackPointSpend)
	{
		PlayAnimation(ANIMATION_SUPER_ATTACK, false);

		m_ActionType = ACTION_SUPER_ATTACK;
		m_SuperAttackPoint -= m_SuperAttackPointSpend;
		m_AttackHitFlag = true;
		if (m_IsBoss)
		{
			BattleManager::GetInstance()->AddSuperAttackNum();
		}

		m_SuperAttackFlag = false;
	}
}

MV1_COLL_RESULT_POLY_DIM CharacterBase::CheckCollisionSphere(VECTOR pos, float r)
{
	DxLib::MV1RefreshCollInfo(m_Handle, -1);

	return MV1CollCheck_Sphere(m_Handle, -1, pos, r);
}

void CharacterBase::HitStage(MapBase* map)
{
	float characterRadius = m_Sphere->GetRadius();

	MV1_COLL_RESULT_POLY_DIM hitResult = map->CheckCollisionSphere(m_Sphere->GetWorldPos(), m_Sphere->GetRadius());

	for (int i = 0; i < hitResult.HitNum; i++)
	{
		MV1_COLL_RESULT_POLY polygon = hitResult.Dim[i];

		float slope = polygon.Normal.y;
		float hitHeight = polygon.HitPosition.y;

		float hitHeightDiff = fabsf(hitHeight - m_Pos.y);

		if (polygon.Normal.y <= 0.1f)
		{			
			if (hitHeightDiff >= 6.0f)
			{
				float dot = VDot(polygon.Normal, m_Move);

				if (dot < 0.0f)
				{
					if (polygon.Normal.x * polygon.Normal.x <= 0.1f)
					{
						m_Pos.z = m_PrevPos.z;
						m_Move.z = 0.0f;
					}
					if (polygon.Normal.z * polygon.Normal.z <= 0.1f)
					{
						m_Pos.x = m_PrevPos.x;
						m_Move.x = 0.0f;
					}
				}
				continue;
			}
		}

		VECTOR spherePos = m_Sphere->GetWorldPos();
		VECTOR lineStart = spherePos;
		VECTOR lineEnd = spherePos;

		lineStart.y += characterRadius;
		lineEnd.y -= characterRadius * 2.0f;

		HITRESULT_LINE lineResult = HitCheck_Line_Triangle(
			lineStart, lineEnd, polygon.Position[0], polygon.Position[1],
			polygon.Position[2]);

		if (!lineResult.HitFlag) continue;

		m_Pos.y = lineResult.Position.y;

		m_Move.y = 0.0f;

		m_Randing = true;
	}

	MV1SetPosition(m_Handle, m_Pos);

	MV1CollResultPolyDimTerminate(hitResult);
}

void CharacterBase::HitBullet(BulletBase* bullet)
{
	if (m_IsBoss == bullet->IsBoss()) return;

	Damage(bullet->GetShooter(), (int)((float)bullet->GetDamage() * bullet->GetMagni() / m_DefenceMagni));

	if (bullet->GetType() == POISON_LEAF)
	{
		m_StateList.push_back(STATE_POISONED);
	}

	bullet->HitCharacter();
}

void CharacterBase::HitCharacter(CharacterBase* character)
{
	float myRadius = m_Sphere->GetRadius();
	float targetRadius = character->GetSphere()->GetRadius();
	float totalRadius = myRadius + targetRadius;

	VECTOR myPos = m_Sphere->GetWorldPos();
	VECTOR targetPos = character->GetSphere()->GetWorldPos();

	VECTOR dirXZ = VGet(myPos.x - targetPos.x, 0.0f, myPos.z - targetPos.z);

	float distaceXZ = VSize(dirXZ);

	if (distaceXZ < 0.001f) return;

	// 重なった時の押し出し
	if (distaceXZ < totalRadius)
	{
		VECTOR normalXZ = VNorm(dirXZ);

		float overlap = totalRadius - distaceXZ;

		float pushStrength = 0.1f;
		VECTOR pushVector = VScale(normalXZ, overlap * pushStrength);

		m_Pos = VAdd(m_Pos, pushVector);

		float moveDot = VDot(m_Move, normalXZ);
		if (moveDot < 0.0f)
		{
			m_Move = VSub(m_Move, VScale(normalXZ, moveDot));
		}
	}

	MV1SetPosition(m_Handle, m_Pos);
}

void CharacterBase::Damage(CharacterBase* opponent, int damage)
{
	if (m_Dead) return;

	m_Hp -= damage;

	BattleManager* battleManager = BattleManager::GetInstance();

	if (m_IsBoss)
	{
		battleManager->ResetNoDamageTimer();
	}

	if (m_Hp > 0)
	{
		if (!m_IsBoss)
		{
			PlayAnimation(ANIMATION_DAMAGED, false);

			m_ActionType = ACTION_DAMAGED;
		}
	}
	else
	{
		m_Dead = true;
		m_StateList.clear();
		PlayAnimation(ANIMATION_DIE, false);
		m_ActionType = ACTION_DIE;
		opponent->AddKilledNum();
		if (m_IsBoss) battleManager->ChildWin();
	}
}

void CharacterBase::HPHeal(int amount)
{
	EffekseerManager::GetInstance()->PlayEffect(EFFEKSEER_HP_HEAL, m_Pos);

	m_Hp += amount;

	if (m_Hp > m_MaxHp)
	{
		m_Hp = m_MaxHp;
	}
}

void CharacterBase::AddPowerMagni(float magni)
{
	EffekseerManager::GetInstance()->PlayEffect(EFFEKSEER_POWER_UP, m_Pos);

	m_PowerMagni *= magni;
}

void CharacterBase::AddDefenceMagni(float magni)
{
	EffekseerManager::GetInstance()->PlayEffect(EFFEKSEER_DEFENCE_UP, m_Pos);

	m_DefenceMagni *= magni;
}

void CharacterBase::SetPosAndIndex(int index, int parentNum)
{
	m_Index = index;

	if (m_IsBoss)
	{
		m_Pos = PARENT_DEFAULT_POS;
	}
	else
	{
		m_Pos = CHILD_DEFAULT_POS;
		if (index < parentNum)
		{
			m_Pos.x -= 40.0f * index;
		}
		else
		{
			m_Pos.x -= 40.0f * (index - 1);
		}
	}
}

bool CharacterBase::CheckHitCoin()
{
	const auto& itemList = ItemManager::GetInstance()->GetItemList();

	bool isAnyHit = false;

	for (auto* item : itemList)
	{
		if (item == nullptr || !item->IsActive()) continue;

		CollisionAABB* coinAABB = item->GetAABB();

		HitResultAABB result = m_AABB->CheckAABB(coinAABB);

		if (result.m_IsHit)
		{
			m_SuperAttackPoint += 10;

			item->Delete();

			isAnyHit = true;
		}
	}

	return isAnyHit;
}

void CharacterBase::Poison()
{
	int hpDecrease = m_MaxHp / 16;

	m_Hp -= hpDecrease;

	if (m_Hp < 0)
	{
		m_Dead = true;
		PlayAnimation(ANIMATION_DIE, false);
		m_ActionType = ACTION_DIE;
		if (m_IsBoss) BattleManager::GetInstance()->ChildWin();
	}
}

MV1_COLL_RESULT_POLY CharacterBase::CheckObstacleTarget(CharacterBase* target)
{
	// 自身の中心
	VECTOR thisCenter = MyMath::VecAdd(m_Pos, MyMath::VecY(m_Radius));

	// ターゲットの中心
	VECTOR targetCenter = MyMath::VecAdd(target->GetPos(), MyMath::VecY(target->GetRadius()));

	VECTOR toTarget = MyMath::VecCreate(thisCenter, targetCenter);
	VECTOR toTargetNormal = VNorm(toTarget);

	// ターゲットに向けてのベクトル
	VECTOR targetDir = MyMath::VecCreate(thisCenter, targetCenter);
	float targetDistance = VSize(targetDir);

	VECTOR targetDirNormal = VNorm(targetDir);

	VECTOR rayEnd = MyMath::VecZero();

	// ターゲットが遠い場合
	if (targetDistance > OBSTACLE_SEARCH_LENGTH * 2)
	{
		VECTOR ray = MyMath::VecScale(targetDirNormal, OBSTACLE_SEARCH_LENGTH * 2);
		rayEnd = MyMath::VecAdd(thisCenter, ray);
	}
	// ターゲットが近い場合
	else
	{
		rayEnd = targetCenter;
	}

	int mapCollisionHandle = MapManager::GetInstance()->GetCurrentMap()->GetCollisionHandle();
	DrawLine3D(thisCenter, rayEnd, GetColor(255, 0, 0));

	return MV1CollCheck_Line(mapCollisionHandle, -1, thisCenter, rayEnd);
}

MV1_COLL_RESULT_POLY_DIM CharacterBase::CheckObstacleForward(bool isRight)
{
	// 自身の中心
	VECTOR thisCenter = MyMath::VecAdd(m_Pos, MyMath::VecY(m_Radius));

	VECTOR forward = VGet(sinf(m_Rot.y), 0.0f, cosf(m_Rot.y));
	VECTOR forwardNormal = VNorm(forward);

	VECTOR centerToSide = MyMath::VecZero();

	// 右端
	if (isRight)
	{
		centerToSide = VGet(-forwardNormal.z, 0.0f, forwardNormal.x);
	}
	// 左端
	else
	{
		centerToSide = VGet(forwardNormal.z, 0.0f, -forwardNormal.x);
	}

	VECTOR rayStart = VAdd(thisCenter, VScale(VNorm(centerToSide), m_Radius * 1.2f));
	
	VECTOR rayEnd = VAdd(rayStart, VScale(forwardNormal, OBSTACLE_SEARCH_LENGTH));

	int mapCollisionHandle = MapManager::GetInstance()->GetCurrentMap()->GetCollisionHandle();
	DrawLine3D(rayStart, rayEnd, GetColor(0, 0, 255));

	return MV1CollCheck_LineDim(mapCollisionHandle, -1, rayStart, rayEnd);
}

void CharacterBase::PlayAnimation(CharacterAnimationType anim, bool isLoop)
{
	if (anim == m_NowAnimation) return;

	if (m_AnimationAttachIndex != -1)
	{
		if (m_PrevAnimationAttachIndex != -1)
		{
			MV1DetachAnim(m_Handle, m_PrevAnimationAttachIndex);
		}
		m_PrevAnimationAttachIndex = m_AnimationAttachIndex;
		m_BlendTime = 0.0f;
	}

	m_AnimationAttachIndex = MV1AttachAnim(m_Handle, anim);

	m_AnimationTotalTime = m_AnimTotalTimes[anim];

	m_AnimationNowTime = 0.0f;

	m_IsLoopAnimation = isLoop;

	m_NowAnimation = anim;
}

void CharacterBase::UpdateAnimation()
{
	if (m_AnimationAttachIndex == -1) return;

	m_AnimationNowTime += ANIMATION_SPEED;

	if (m_AnimationNowTime >= m_AnimationTotalTime)
	{
		if (m_IsLoopAnimation)
		{
			m_AnimationNowTime = 0.0f;
		}
		else
		{
			m_AnimationNowTime = m_AnimationTotalTime;

			if (m_ActionType != ACTION_DIE)
			{
				m_ActionType = ACTION_TYPE_NONE;

				PlayAnimation(ANIMATION_STOP, true);
			}
		}
	}
		
	MV1SetAttachAnimTime(m_Handle, m_AnimationAttachIndex, m_AnimationNowTime);

	if (m_PrevAnimationAttachIndex != -1)
	{
		m_BlendTime += ANIMATION_SPEED;

		if (m_BlendTime >= BLEND_DURATION)
		{
			MV1DetachAnim(m_Handle, m_PrevAnimationAttachIndex);
			m_PrevAnimationAttachIndex = -1;

			MV1SetAttachAnimBlendRate(m_Handle, m_AnimationAttachIndex, 1.0f);
		}
		else
		{
			float rate = m_BlendTime / BLEND_DURATION;
			MV1SetAttachAnimBlendRate(m_Handle, m_PrevAnimationAttachIndex, 1.0f - rate);
			MV1SetAttachAnimBlendRate(m_Handle, m_AnimationAttachIndex, rate);
		}
	}
	else
	{
		if (m_AnimationAttachIndex != -1)
		{
			MV1SetAttachAnimBlendRate(m_Handle, m_AnimationAttachIndex, 1.0f);
		}
	}
}

