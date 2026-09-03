#include "DxLib.h"
#include "OptionScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Character/CharacterManager.h"
#include "../Mission/MissionManager.h"
#include "../Camera/CameraManager.h"
#include "../UI/UIManager.h"
#include "../UI/UIButton.h"
#include "../MyMath/MyMath.h"
#include "../Sound/SoundManager.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"

const VECTOR UI_BUTTON_SOUND_POS = VGet(400.0f, 300.0f, 0.0f);
const VECTOR UI_BUTTON_MANUAL_POS = VGet(400.0f, 600.0f, 0.0f);
const VECTOR UI_BUTTON_BGM_POS = VGet(800.0f, 400.0f, 0.0f);
const VECTOR UI_BUTTON_SE_POS = VGet(800.0f, 700.0f, 0.0f);
const VECTOR BGM_VOLUME_MIN_POS = VGet(1000.0f, 400.0f, 0.0f);
const VECTOR SE_VOLUME_MIN_POS = VGet(1000.0f, 700.0f, 0.0f);
const VECTOR BGM_VOLUME_MAX_POS = VGet(1400.0f, 400.0f, 0.0f);
const VECTOR SE_VOLUME_MAX_POS = VGet(1400.0f, 700.0f, 0.0f);
const VECTOR MANUAL_IMAGE_POS = VGet(1100.0f, 450.0f, 0.0f);
const int SOUND_VOLUME_MAX = 100;

OptionScene::OptionScene() : SceneBase()
{
	m_BGMVolumePos = MyMath::VecZero();
	m_SEVolumePos = MyMath::VecZero();

	m_BGMVolumeHandle = 0;
	m_SEVolumeHandle = 0;
	m_ManualHandle = 0;

	m_IsBGMSetMode = false;
	m_IsSESetMode = false;

	m_ModeType = MODE_TYPE_NONE;
}

OptionScene::~OptionScene()
{

}

void OptionScene::Init()
{

}

void OptionScene::Load()
{
	m_BGHandle = LoadGraph("Data/BackGround/MissionSelectScene.png");
	m_BGMVolumeHandle = LoadGraph("Data/UI/OptionScene/VolumeIcon.png");
	m_SEVolumeHandle = LoadGraph("Data/UI/OptionScene/VolumeIcon.png");
	m_ManualHandle = LoadGraph("Data/UI/OptionScene/ManualImage.png");
}

void OptionScene::Start()
{
	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlayBGM(BGM_HOME);

	m_BGMVolumePos = BGM_VOLUME_MIN_POS;
	m_SEVolumePos = SE_VOLUME_MIN_POS;
	
	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Start();
	uiManager->CreateUIButton(UI_BUTTON_SOUND, UI_BUTTON_SOUND_POS, MyMath::Vec2DInt(1, 1));
	uiManager->CreateUIButton(UI_BUTTON_MANUAL, UI_BUTTON_MANUAL_POS, MyMath::Vec2DInt(1, 2));
	uiManager->CreateUIButton(UI_BUTTON_BGM, UI_BUTTON_BGM_POS, MyMath::Vec2DInt(2, 1));
	uiManager->CreateUIButton(UI_BUTTON_SE, UI_BUTTON_SE_POS, MyMath::Vec2DInt(2, 2));
	uiManager->SetTotalButtonIndex(MyMath::Vec2DInt(2, 2));

	// "BGM"と"SE"のUIははじめは描画しない
	UIBase* bgm = uiManager->GetUI(UI_BUTTON_BGM);
	UIBase* se = uiManager->GetUI(UI_BUTTON_SE);
	bgm->SetActive(false);
	se->SetActive(false);
}

void OptionScene::Step()
{
	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Step();

	Sound* sound = SoundManager::GetInstance()->GetSound();

	if (Input::IsTriggerButton(Input::BUTTON_A))
	{
		sound->PlaySE(SE_CANCEL);

		if (m_IsBGMSetMode)
		{
			m_IsBGMSetMode = false;
			uiManager->SetXFixed(false);
			uiManager->SetYFixed(false);
		}
		else if (m_IsSESetMode)
		{
			m_IsSESetMode = false;
			uiManager->SetXFixed(false);
			uiManager->SetYFixed(false);
		}
		else
		{
			if (!m_SceneChangeStart)
			{
				FPSSystem* fps = FPSManager::GetInstance()->GetFPS();
				Event::SetStartCount();

				Sound* sound = SoundManager::GetInstance()->GetSound();
				sound->PlaySE(SE_CANCEL);
			}

			m_SceneChangeStart = true;
		}
	}

	if (Input::IsTriggerButton(Input::BUTTON_B))
	{
		sound->PlaySE(SE_CURSOR_SELECT);

		UIName uiName = uiManager->GetSelectedName();

		if (uiName == UI_BUTTON_BGM)
		{
			m_IsBGMSetMode = true;
			uiManager->SetXFixed(true);
			uiManager->SetYFixed(true);
		}
		else if (uiName == UI_BUTTON_SE)
		{
			m_IsSESetMode = true;
			uiManager->SetXFixed(true);
			uiManager->SetYFixed(true);
		}
	}
}

void OptionScene::Update()
{
	SceneBase::Update();

	UIManager* uiManager = UIManager::GetInstance();
	uiManager->Update();

	UIBase* bgmUI = uiManager->GetUI(UI_BUTTON_BGM);
	UIBase* seUI = uiManager->GetUI(UI_BUTTON_SE);
	switch (uiManager->GetSelectedName())
	{
	case UI_BUTTON_SOUND:
	{
		m_ModeType = SOUND;
		// サウンド設定モードになったらUIを有効化
		uiManager->SetXFixed(false);
		bgmUI->SetActive(true);
		seUI->SetActive(true);
		break;
	}
	case UI_BUTTON_MANUAL:
	{
		m_ModeType = MANUAL;
		uiManager->SetXFixed(true);
		bgmUI->SetActive(false);
		seUI->SetActive(false);
		break;
	}
	default:
		break;
	}

	if (m_IsBGMSetMode)
	{
		BGMSet();
	}
	if (m_IsSESetMode)
	{
		SESet();
	}

	SetVolumePos();

	if (m_SceneChangeEnd)
	{
		SceneManager::GetInstance()->ChangeScene(HOME);
	}
}

void OptionScene::Draw()
{
	DrawGraph(0, 0, m_BGHandle, TRUE);

	int bgmBarColor = 128;
	int	seBarColor = 128;
	if (m_IsBGMSetMode) bgmBarColor = 255;
	if (m_IsSESetMode) seBarColor = 255;

	switch (m_ModeType)
	{
	case SOUND:
		DrawBox((int)BGM_VOLUME_MIN_POS.x - 30, (int)BGM_VOLUME_MIN_POS.y - 10, (int)BGM_VOLUME_MAX_POS.x + 30, (int)BGM_VOLUME_MAX_POS.y + 10,
			GetColor(bgmBarColor, bgmBarColor, bgmBarColor), TRUE);
		DrawBox((int)SE_VOLUME_MIN_POS.x - 30, (int)SE_VOLUME_MIN_POS.y - 10, (int)SE_VOLUME_MAX_POS.x + 30, (int)SE_VOLUME_MAX_POS.y + 10,
			GetColor(seBarColor, seBarColor, seBarColor), TRUE);
		DrawRotaGraph((int)m_BGMVolumePos.x, (int)m_BGMVolumePos.y, 1.0, 0.0, m_BGMVolumeHandle, TRUE);
		DrawRotaGraph((int)m_SEVolumePos.x, (int)m_SEVolumePos.y, 1.0, 0.0, m_SEVolumeHandle, TRUE);
		break;
	case MANUAL:
		DrawRotaGraph((int)MANUAL_IMAGE_POS.x, (int)MANUAL_IMAGE_POS.y, 1.0, 0.0, m_ManualHandle, TRUE);
		break;
	case MODE_TYPE_MAX:
		break;
	case MODE_TYPE_NONE:
		break;
	default:
		break;
	}

	UIManager::GetInstance()->Draw();
}

void OptionScene::Fin()
{
	UIManager::GetInstance()->ResetUI();

	DeleteGraph(m_BGHandle);
}

void OptionScene::BGMSet()
{
	Sound* sound = SoundManager::GetInstance()->GetSound();
	int volume = sound->GetBGMVolume();

	if (Input::GetLeftStickX() > 500)
	{
		volume++;
	}
	else if (Input::GetLeftStickX() < -500)
	{
		volume--;
	}

	if (volume > SOUND_VOLUME_MAX || volume < 0)
	{
		return;
	}

	sound->SetBGMVolume(volume);
}

void OptionScene::SESet()
{
	Sound* sound = SoundManager::GetInstance()->GetSound();
	int volume = sound->GetSEVolume();

	if (Input::GetLeftStickX() > 500)
	{
		volume++;
	}
	else if (Input::GetLeftStickX() < -500)
	{
		volume--;
	}

	if (volume > SOUND_VOLUME_MAX || volume < 0)
	{
		return;
	}

	sound->SetSEVolume(volume);
}

void OptionScene::SetVolumePos()
{
	Sound* sound = SoundManager::GetInstance()->GetSound();
	int bgmVolume = sound->GetBGMVolume();
	int bgmLange = (int)(BGM_VOLUME_MAX_POS.x - BGM_VOLUME_MIN_POS.x);

	m_BGMVolumePos.x = BGM_VOLUME_MIN_POS.x + bgmLange / SOUND_VOLUME_MAX * bgmVolume;

	int seVolume = sound->GetSEVolume();
	int seLange = (int)(SE_VOLUME_MAX_POS.x - SE_VOLUME_MIN_POS.x);

	m_SEVolumePos.x = SE_VOLUME_MIN_POS.x + seLange / SOUND_VOLUME_MAX * seVolume;
}