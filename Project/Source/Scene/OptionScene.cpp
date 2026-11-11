#include "DxLib.h"
#include "OptionScene.h"
#include "SceneManager.h"
#include "../Input/Input.h"
#include "../Managers/CharacterManager/CharacterManager.h"
#include "../Managers/CameraManager/CameraManager.h"
#include "../MyMath/MyMath.h"
#include "../Sound/SoundManager.h"
#include "../FPS/FPSManager.h"
#include "../Event/Event.h"
#include "../Managers/RendererManager/RendererManager.h"

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
	m_BGMVolumeHandle = LoadGraph("Data/UI/OptionScene/VolumeIcon.png");
	m_SEVolumeHandle = LoadGraph("Data/UI/OptionScene/VolumeIcon.png");
	m_ManualHandle = LoadGraph("Data/UI/OptionScene/ManualImage.png");
}

void OptionScene::Start()
{
	SceneBase::Start();

	m_ModeType = MODE_OPTION;

	Sound* sound = SoundManager::GetInstance()->GetSound();
	sound->PlayBGM(BGM_HOME);

	m_BGMVolumePos = BGM_VOLUME_MIN_POS;
	m_SEVolumePos = SE_VOLUME_MIN_POS;

	RendererManager* rendererManager = RendererManager::GetInstance();

	auto optionGroupObj = rendererManager->CreateButtonGroup(GROUP_NAME_OPTION);
	auto soundGroupObj = rendererManager->CreateButtonGroup(GROUP_NAME_SOUND);

	m_OptionGroup = optionGroupObj->GetComponent<UIButtonGroup>();
	m_SoundGroup = soundGroupObj->GetComponent<UIButtonGroup>();

	auto bgObj = rendererManager->CreateBackGround("Data/BackGround/MissionSelectScene.png");
	auto buttonSoundObj = rendererManager->CreateUIButton("Data/UI/OptionScene/Sound.png", MyMath::Vec2D(400.0f, 300.0f), VGet(1.0f, 1.0f, 1.0f), 0.0, MyMath::Vec2DInt(1, 1), m_OptionGroup);
	auto buttonManualObj = rendererManager->CreateUIButton("Data/UI/OptionScene/Manual.png", MyMath::Vec2D(400.0f, 600.0f), VGet(1.0f, 1.0f, 1.0f), 0.0, MyMath::Vec2DInt(1, 2), m_OptionGroup);
	auto buttonBGMObj = rendererManager->CreateUIButton("Data/UI/OptionScene/BGM.png", MyMath::Vec2D(800.0f, 400.0f), VGet(1.0f, 1.0f, 1.0f), 0.0, MyMath::Vec2DInt(1, 1), m_SoundGroup);
	auto buttonSEObj = rendererManager->CreateUIButton("Data/UI/OptionScene/SE.png", MyMath::Vec2D(800.0f, 700.0f), VGet(1.0f, 1.0f, 1.0f), 0.0, MyMath::Vec2DInt(1, 2), m_SoundGroup);

	auto optionGroupPtr = m_OptionGroup.lock();
	auto soundGroupPtr = m_SoundGroup.lock();

	if (!optionGroupPtr || !soundGroupPtr) return;
	
	optionGroupPtr->SetTotalIndex(MyMath::Vec2DInt(1, 2));
	soundGroupPtr->SetTotalIndex(MyMath::Vec2DInt(1, 2));

	optionGroupPtr->SetActive(true);
	soundGroupPtr->SetActive(false);
	soundGroupPtr->SetInactiveInvisible(true);

	Instantiate(optionGroupObj);
	Instantiate(soundGroupObj);
	Instantiate(bgObj);
	Instantiate(buttonSoundObj);
	Instantiate(buttonManualObj);
	Instantiate(buttonBGMObj);
	Instantiate(buttonSEObj);

	m_IsBGMSetMode = false;
	m_IsSESetMode = false;
	m_ModeType = MODE_OPTION;
}

void OptionScene::Step()
{
	Sound* sound = SoundManager::GetInstance()->GetSound();

	RendererManager* rendererManager = RendererManager::GetInstance();
	rendererManager->CheckCursor(m_UIInputCmp);
	
	RendererManager::GetInstance()->CheckCursor(m_UIInputCmp);

	auto optionGroupPtr = m_OptionGroup.lock();
	auto soundGroupPtr = m_SoundGroup.lock();

	if (!optionGroupPtr || !soundGroupPtr) return;

	switch (m_ModeType)
	{
	case MODE_OPTION:
		if (optionGroupPtr->GetCurrentIndex().y == 1)
		{
			m_ModeType = MODE_OPTION;
			if (m_UIInputCmp->IsTriggerUI(INPUT_SELECT))
			{
				soundGroupPtr->SetActive(true);

				m_ModeType = MODE_SOUND;

				optionGroupPtr->SetActive(false);
				sound->PlaySE(SE_CURSOR_SELECT);
			}
		}
		else if (optionGroupPtr->GetCurrentIndex().y == 2)
		{
			m_ModeType = MODE_MANUAL;
		}
		break;
	case MODE_SOUND:
		if (soundGroupPtr->GetCurrentIndex().y == 1)
		{
			m_IsBGMSetMode = true;
			m_IsSESetMode = false;
		}
		else if (soundGroupPtr->GetCurrentIndex().y == 2)
		{
			m_IsBGMSetMode = false;
			m_IsSESetMode = true;
		}
		break;
	case MODE_MANUAL:
		if (optionGroupPtr->GetCurrentIndex().y != 2)
		{
			m_ModeType = MODE_OPTION;
		}
		break;
	case MODE_TYPE_MAX:
		break;
	case MODE_TYPE_NONE:
		break;
	default:
		break;
	}

	if (m_UIInputCmp->IsTriggerUI(INPUT_CANCEL))
	{
		if (m_ModeType == MODE_SOUND)
		{
			soundGroupPtr->SetActive(false);
			optionGroupPtr->SetActive(true);
			m_ModeType = MODE_OPTION;
			m_IsBGMSetMode = false;
			m_IsSESetMode = false;
		}
		else
		{
			Event::SetStartCount();
		}

		sound->PlaySE(SE_CANCEL);
	}
}

void OptionScene::Update()
{
	SceneBase::Update();

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
	SceneBase::Draw();

	int bgmBarColor = 128;
	int	seBarColor = 128;
	if (m_IsBGMSetMode) bgmBarColor = 255;
	if (m_IsSESetMode) seBarColor = 255;

	switch (m_ModeType)
	{
	case MODE_SOUND:
		DrawBox((int)BGM_VOLUME_MIN_POS.x - 30, (int)BGM_VOLUME_MIN_POS.y - 10, (int)BGM_VOLUME_MAX_POS.x + 30, (int)BGM_VOLUME_MAX_POS.y + 10,
			GetColor(bgmBarColor, bgmBarColor, bgmBarColor), TRUE);
		DrawBox((int)SE_VOLUME_MIN_POS.x - 30, (int)SE_VOLUME_MIN_POS.y - 10, (int)SE_VOLUME_MAX_POS.x + 30, (int)SE_VOLUME_MAX_POS.y + 10,
			GetColor(seBarColor, seBarColor, seBarColor), TRUE);
		DrawRotaGraph((int)m_BGMVolumePos.x, (int)m_BGMVolumePos.y, 1.0, 0.0, m_BGMVolumeHandle, TRUE);
		DrawRotaGraph((int)m_SEVolumePos.x, (int)m_SEVolumePos.y, 1.0, 0.0, m_SEVolumeHandle, TRUE);
		break;
	case MODE_MANUAL:
		DrawRotaGraph((int)MANUAL_IMAGE_POS.x, (int)MANUAL_IMAGE_POS.y, 1.0, 0.0, m_ManualHandle, TRUE);
		break;
	case MODE_TYPE_MAX:
		break;
	case MODE_TYPE_NONE:
		break;
	default:
		break;
	}
}

void OptionScene::Fin()
{
	SceneBase::Fin();
}

void OptionScene::BGMSet()
{
	Sound* sound = SoundManager::GetInstance()->GetSound();
	int volume = sound->GetBGMVolume();

	if (m_UIInputCmp->IsInputUI(CURSOR_RIGHT))
	{
		volume++;
	}
	else if (m_UIInputCmp->IsInputUI(CURSOR_LEFT))
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

	if (m_UIInputCmp->IsInputUI(CURSOR_RIGHT))
	{
		volume++;
	}
	else if (m_UIInputCmp->IsInputUI(CURSOR_LEFT))
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