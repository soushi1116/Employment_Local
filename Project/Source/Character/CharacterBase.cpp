#include "CharacterBase.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../Map/MapManager.h"
#include "../Map/Map.h"
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

const int RESPAWN_INTERVAL = 180;
const int PARENT_MAX_HP = 500;
const int CHILD_MAX_HP = 30;

const float ANIMATION_SPEED = 1.0f;
const float GRAVITY = 0.01f;
const float BLEND_DURATION = 0.2f;

const VECTOR PARENT_DEFAULT_POS = VGet(0.0f, 0.0f, -100.0f);
const VECTOR CHILD_DEFAULT_POS = VGet(40.0f, 0.0f, 100.0f);

const VECTOR UI_SKILL_POS = VGet(175.0f, 775.0f, 0.0f);
const VECTOR UI_SUPER_ATTACK_POS = VGet(475.0f, 775.0f, 0.0f);
const float UI_SKILL_AND_SUPER_ATTACK_RADIUS = 75.0f;

CharacterBase::CharacterBase()
{
	m_Pos = MyMath::VecZero();
	m_PrevPos = MyMath::VecZero();
	m_Rot = MyMath::VecZero();
	m_Scale = MyMath::VecZero();
	m_Move = MyMath::VecZero();
	m_DefaultPos = MyMath::VecZero();
	m_Active = false;
	m_Randing = false;
	m_AttackHitFlag = false;
	m_Dead = false;
	m_IsBoss = false;
	m_InBattleScene = false;
	m_IsPlayer = false;
	m_Invisible = false;
	m_Power = 0;
	m_Speed = 0.0f;
	m_Radius = 0.0f;
	m_SuperAttackRange = 0.0f;
	m_Hp = 0;
	m_MaxHp = 0;
	m_RespawnTimer = 0;
	m_Index = 0;
	m_SkillPoint = 0;
	m_SuperAttackPoint = 0;
	m_KilledNum = 0;
	m_SkillPointSpend = 0;
	m_SuperAttackPointSpend = 0;
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

	m_Handle = 0;

	for (int i = 0; i < ANIMATION_MAX; i++)
	{
		m_AnimTotalTimes[i] = 0.0f;
	}

	m_SkillFlag = false;
	m_SuperAttackFlag = false;

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
}

void CharacterBase::Start()
{
	m_Scale = VGet(10.0f, 10.0f, 10.0f);

	if (m_IsBoss)
	{
		m_MaxHp = PARENT_MAX_HP;
		m_Scale = MyMath::VecScale(m_Scale, 1.2f);
	}
	else
	{
		m_MaxHp = CHILD_MAX_HP;
	}

	m_DefaultPos = m_Pos;
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
		//CPUMove();
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

	m_Randing = false;

	UpdateAnimation();

	/*MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);*/

	DxLib::MV1RefreshCollInfo(m_Handle, -1);
}

void CharacterBase::PlayerMove()
{
	if (m_ActionType != ACTION_SUPER_ATTACK
		&& m_ActionType != ACTION_ATTACK)
	{
		m_AttackHitFlag = false;
	}

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

						continue;
					}
				}
			}
		}

		if (m_Target != nullptr)
		{
			targetPos = m_Target->GetPos();
		}

		VECTOR moveDir = MyMath::VecCreate(m_Pos, targetPos);

		float targetDistance = MyMath::VecLong(moveDir);

		VECTOR moveDirNormal = MyMath::VecNormarize(moveDir);

		if (m_Target != nullptr && m_ActionType == ACTION_TYPE_NONE)
		{
			m_Rot.y = atan2f(moveDirNormal.x, moveDirNormal.z);

			if (targetDistance >= 20.0f)
			{
				m_Move.x = m_Speed * moveDirNormal.x;
				m_Move.z = m_Speed * moveDirNormal.z;
			}
			else
			{
				Attack();
			}

			if (m_SuperAttackFlag && targetDistance < m_SuperAttackRange)
			{
				SuperAttack();
			}
		}

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
			if (!m_IsBoss)
			{
				m_RespawnTimer++;

				if (m_RespawnTimer > RESPAWN_INTERVAL)
				{
					Respawn(m_DefaultPos);
					m_RespawnTimer = 0;
				}
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
	if (m_IsPlayer)
	{
		DrawFormatString(m_Index * 350 + 100, 800, GetColor(255, 255, 255), "Player[%d, %d, %f]", m_Hp, m_Power, m_Speed);
		DrawBox(200, 50, 600, 80, GetColor(255, 255, 255), TRUE);
		if (m_Hp > 0)
		{
			DrawBox(200, 50, 200 + 400 * m_Hp / m_MaxHp, 80, GetColor(0, 255, 0), TRUE);
		}

		DrawCircleGauge(
			(int)UI_SKILL_POS.x, (int)UI_SKILL_POS.y,
			m_SkillPoint + 50.0, m_SkillGaugeHandle, 50.0, 1.1);

		DrawCircleGauge((int)UI_SUPER_ATTACK_POS.x, (int)UI_SUPER_ATTACK_POS.y,
			m_SuperAttackPoint + 50.0, m_SuperAttackGaugeHandle, 50.0, 1.1);
	}
	else
	{
		DrawFormatString(m_Index * 350 + 100, 800, GetColor(255, 255, 255), "Enemy[%d, %d, %f]", m_Hp, m_Power, m_Speed);
	}
	
	if (m_IsPlayer)
	{
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%f, %f, %f", m_Pos.x, m_Pos.y, m_Pos.z);

		UIManager::GetInstance()->Draw();
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

	m_AttackHitFlag = true;
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

void CharacterBase::HitStage(Map* map)
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

	Damage(bullet->GetShooter(), bullet->GetDamage());

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
		PlayAnimation(ANIMATION_DIE, false);
		m_ActionType = ACTION_DIE;
		opponent->AddKilledNum();
		if (m_IsBoss) battleManager->ChildWin();
	}
}

void CharacterBase::SetColor()
{
	COLOR_F color = GetColorF(0.0f, 0.0f, 0.0f, 0.0f);

	switch (m_Index)
	{
	case 0:
		color = GetColorF(1.0f, 0.0f, 0.0f, 1.0f);
		break;
	case 1:
		color = GetColorF(0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 2:
		color = GetColorF(0.0f, 1.0f, 0.0f, 1.0f);
		break;
	case 3:
		color = GetColorF(1.0f, 1.0f, 0.0f, 1.0f);
		break;
	default:
		break;
	}

	SetUseLighting(FALSE);

	MV1SetDifColorScale(m_Handle, color);
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
			m_ActionType = ACTION_TYPE_NONE;

			PlayAnimation(ANIMATION_STOP, true);
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