#include "RendererManager.h"
#include "../../Component/Component.h"
#include "../../Component/GameObject.h"
#include "../../Component/AllComponents.h"
#include "../../MyColor/MyColor.h"

const VECTOR BATTLE_UI_DEFAULT_POS = MyMath::Vec2D(200.0f, 100.0f);
const VECTOR RESULT_UI_DEFAULT_POS = MyMath::Vec2D(450.0f, 400.0f);

const VECTOR ICON_POS_OFFSET = MyMath::Vec2D(100.0f, 0.0f);
const VECTOR NAME_POS_OFFSET = MyMath::Vec2D(-130.0f, -30.0f);
const VECTOR HP_BAR_POS_OFFSET = MyMath::Vec2D(-50.0f, 30.0f);
const VECTOR HP_GAUGE_POS_OFFSET = MyMath::Vec2D(-102.0f, -51.0f);
const float FRAME_POS_X_INTERVAL_RESULT = 700.0f;
const float FRAME_POS_Y_INTERVAL = 150.0f;

const VECTOR SKILL_UI_POS = MyMath::Vec2D(200.0f, 800.0f);
const VECTOR SUPER_ATTACK_UI_POS = MyMath::Vec2D(500.0f, 800.0f);

RendererManager* RendererManager::m_Instance = nullptr;

RendererManager::RendererManager()
{
	m_FontHandle[TIMER_TEXT] = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 40, -1);
	m_FontHandle[NAME_BATTLE_SCENE] = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 42, -1);
	m_FontHandle[NAME_RESULT_SCENE] = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 84, -1);
	m_FontHandle[MISSION_TEXT] = CreateFontToHandle("HGS創英角ﾎﾟｯﾌﾟ体", 30, -1);
}

RendererManager::~RendererManager()
{

}

void RendererManager::Init()
{

}

void RendererManager::Load()
{

}

void RendererManager::Start()
{
	
}

void RendererManager::Step()
{

}

void RendererManager::Update()
{
	
}

void RendererManager::Draw()
{

}

void RendererManager::Fin()
{

}


std::shared_ptr<GameObject> RendererManager::CreateBackGround(const char* filePath)
{
	auto bgObj = std::make_shared<GameObject>();

	auto backGroundRenderer = bgObj->AddComponent<BackGroundRenderer>(filePath);

	return bgObj;
}

std::shared_ptr<GameObject> RendererManager::CreateUIImage(const char* filePath, VECTOR pos, VECTOR exRate, float angle)
{
	auto imageObj = std::make_shared<GameObject>();

	auto renderer = imageObj->AddComponent<SpriteRenderer>(filePath);

	renderer->SetPos(pos);
	renderer->SetExRate(exRate);
	renderer->SetAngle(angle);

	return imageObj;
}

std::shared_ptr<GameObject> RendererManager::CreateUIButton(const char* filePath, VECTOR pos, VECTOR exRate, float angle, MyMath::VECTOR_INT index, std::weak_ptr<UIButtonGroup> parent)
{
	auto buttonObj = std::make_shared<GameObject>();

	auto renderer = buttonObj->AddComponent<SpriteRenderer>(filePath);

	renderer->SetPos(pos);
	renderer->SetExRate(exRate);
	renderer->SetAngle(angle);

	auto uiButton = buttonObj->AddComponent<UIButton>("");
	uiButton->SetIndex(index);
	uiButton->SetParent(parent);

	return buttonObj;
}

std::shared_ptr<GameObject> RendererManager::CreateUIText(VECTOR pos, unsigned int color, FontHandleType type, const char* text)
{
	auto textObj = std::make_shared<GameObject>();

	auto renderer = textObj->AddComponent<TextRenderer>("");

	renderer->SetPos(pos);
	renderer->SetColor(color);
	renderer->SetFontType(type);
	renderer->SetText(text);

	return textObj;
}

std::shared_ptr<GameObject> RendererManager::CreateButtonGroup(ButtonGroupName name)
{
	auto groupObj = std::make_shared<GameObject>();

	auto buttonGroup = groupObj->AddComponent<UIButtonGroup>();
	buttonGroup->SetGroupName(name);

	auto timer = groupObj->AddComponent<Timer>();
	buttonGroup->SetCursorTimer(timer);
	timer->CountStart(0.1f);

	m_UIButtonGroups.push_back(buttonGroup);

	return groupObj;
}

std::shared_ptr<GameObject> RendererManager::CreateGauge(const char* filePath, GaugeType type, VECTOR pos, VECTOR exRate, float angle, std::shared_ptr<CharacterParameter> param)
{
	auto gaugeObj = std::make_shared<GameObject>();

	std::shared_ptr<GaugeBase> gaugeCmp = nullptr;

	switch (type)
	{
	case CHARACTER_HP_GAUGE:
	{
		auto lineGauge = gaugeObj->AddComponent<LineGauge>(filePath);
		lineGauge->SetMaxExRateX(exRate.x);
		gaugeCmp = lineGauge;
		break;
	}
	case CHARACTER_SKILL_GAUGE:
		gaugeCmp = gaugeObj->AddComponent<CircleGauge>(filePath);
		break;
	case CHARACTER_SUPER_ATTACK_GAUGE:
		gaugeCmp = gaugeObj->AddComponent<CircleGauge>(filePath);
		break;
	case GAUGE_TYPE_MAX:
		break;
	case GAUGE_TYPE_NONE:
		break;
	default:
		break;
	}
	
	gaugeCmp->SetPos(pos);
	gaugeCmp->SetExRate(exRate);
	gaugeCmp->SetAngle(angle);
	gaugeCmp->SetGaugeType(type);

	gaugeCmp->SetParentParameter(param);

	return gaugeObj;
}

/// <summary>
/// バトル画面用のキャラクターUI作成
/// </summary>
/// <param name="characterParam">各キャラクターのパラメーター</param>
/// <returns>UIオブジェクトの配列</returns>
std::vector<std::shared_ptr<GameObject>> RendererManager::CreateCharacterBattleUI(std::shared_ptr<CharacterParameter> characterParam)
{
	std::vector<std::shared_ptr<GameObject>> characterUI;

	VECTOR defaultPos = BATTLE_UI_DEFAULT_POS;

	float posYOffset = FRAME_POS_Y_INTERVAL * static_cast<float>(characterParam->GetIndex());

	defaultPos = VAdd(defaultPos, MyMath::VecY(posYOffset));

	// フレーム生成
	std::shared_ptr<GameObject> frameImage = nullptr;

	if (characterParam->IsBoss())
	{
		frameImage = CreateUIImage("Data/UI/BattleScene/BossFrame.png", defaultPos, VGet(1.2f, 1.2f, 1.0f), 0.0f);
	}
	else
	{
		frameImage = CreateUIImage("Data/UI/BattleScene/ChallengerFrame.png", defaultPos, VGet(1.2f, 1.2f, 1.0f), 0.0f);
	}

	characterUI.push_back(frameImage);

	// アイコン生成
	std::shared_ptr<GameObject> iconImage = nullptr;

	VECTOR iconPos = VAdd(defaultPos, ICON_POS_OFFSET);

	switch (characterParam->GetType())
	{
	case CharacterType::KNIGHT:
		iconImage = CreateUIImage("Data/UI/Character/KnightIcon.png", iconPos, VGet(0.6f, 0.6f, 1.0f), 0.0f);
		break;
	case CharacterType::NINJA:
		iconImage = CreateUIImage("Data/UI/Character/NinjaIcon.png", iconPos, VGet(0.6f, 0.6f, 1.0f), 0.0f);
		break;
	case CharacterType::FAIRY:
		iconImage = CreateUIImage("Data/UI/Character/FairyIcon.png", iconPos, VGet(0.6f, 0.6f, 1.0f), 0.0f);
		break;
	case CharacterType::ROBOT:
		iconImage = CreateUIImage("Data/UI/Character/RobotIcon.png", iconPos, VGet(0.6f, 0.6f, 1.0f), 0.0f);
		break;
	case CharacterType::BEAST:
		iconImage = CreateUIImage("Data/UI/Character/BeastIcon.png", iconPos, VGet(0.6f, 0.6f, 1.0f), 0.0f);
		break;
	default:
		break;
	}

	characterUI.push_back(iconImage);

	// 名前生成
	std::shared_ptr<GameObject> nameText = nullptr;

	VECTOR namePos = VAdd(defaultPos, NAME_POS_OFFSET);

	switch (characterParam->GetType())
	{
	case CharacterType::KNIGHT:
		nameText = CreateUIText(namePos, COLOR_BLACK, NAME_BATTLE_SCENE, "Knight");
		break;
	case CharacterType::NINJA:
		nameText = CreateUIText(namePos, COLOR_BLACK, NAME_BATTLE_SCENE, "Ninja");
		break;
	case CharacterType::FAIRY:
		nameText = CreateUIText(namePos, COLOR_BLACK, NAME_BATTLE_SCENE, "Fairy");
		break;
	case CharacterType::ROBOT:
		nameText = CreateUIText(namePos, COLOR_WHITE, NAME_BATTLE_SCENE, "Robot");
		break;
	case CharacterType::BEAST:
		nameText = CreateUIText(namePos, COLOR_WHITE, NAME_BATTLE_SCENE, "Beast");
		break;
	default:
		break;
	}

	characterUI.push_back(nameText);

	// HPフレーム生成
	std::shared_ptr<GameObject> hpBarFrame = nullptr;

	VECTOR hpBarPos = VAdd(defaultPos, HP_BAR_POS_OFFSET);

	if (characterParam->IsBoss())
	{
		hpBarFrame = CreateUIImage("Data/UI/BattleScene/HPBarFrameBoss.png", hpBarPos, VGet(1.7f, 1.0f, 1.0f), 0.0f);
	}
	else
	{
		hpBarFrame = CreateUIImage("Data/UI/BattleScene/HPBarFrameChallenger.png", hpBarPos, VGet(1.7f, 1.0f, 1.0f), 0.0f);
	}

	characterUI.push_back(hpBarFrame);

	// HPゲージ生成
	VECTOR hpGaugePos = VAdd(hpBarPos, HP_GAUGE_POS_OFFSET);

	std::shared_ptr<GameObject> hpGaugeObj = CreateGauge("Data/UI/BattleScene/HPGaugeGreen.png", CHARACTER_HP_GAUGE, hpGaugePos, VGet(1.6f, 0.8f, 1.0f), 0.0f, characterParam);

	characterUI.push_back(hpGaugeObj);

	if (characterParam->IsPlayer())
	{
		// スキルフレーム生成
		auto skillFrameObj = CreateUIImage("Data/UI/BattleScene/Skill.png", SKILL_UI_POS, MyMath::VecSame(1.0f), 0.0f);
		characterUI.push_back(skillFrameObj);

		// スキルゲージ生成
		auto skillGaugeObj = CreateGauge("Data/UI/BattleScene/SkillGauge.png", CHARACTER_SKILL_GAUGE, SKILL_UI_POS, MyMath::VecSame(1.0f), 0.0f, characterParam);
		characterUI.push_back(skillGaugeObj);

		// 必殺技フレーム生成
		auto superAttackFrameObj = CreateUIImage("Data/UI/BattleScene/SuperAttack.png", SUPER_ATTACK_UI_POS, MyMath::VecSame(1.0f), 0.0f);
		characterUI.push_back(superAttackFrameObj);

		// 必殺技ゲージ生成
		auto superAttackGaugeObj = CreateGauge("Data/UI/BattleScene/SuperAttackGauge.png", CHARACTER_SUPER_ATTACK_GAUGE, SKILL_UI_POS, MyMath::VecSame(1.0f), 0.0f, characterParam);
		characterUI.push_back(superAttackGaugeObj);
	}

	return characterUI;

	
}

/// <summary>
/// リザルト画面用のキャラクターUI作成
/// </summary>
/// <param name="characterParam">各キャラクターのパラメーター</param>
/// <returns>UIオブジェクトの配列</returns>
std::vector<std::shared_ptr<GameObject>> RendererManager::CreateCharacterResultUI(std::shared_ptr<CharacterParameter> characterParam, bool bossUICreated)
{
	std::vector<std::shared_ptr<GameObject>> characterUI;

	VECTOR defaultPos = RESULT_UI_DEFAULT_POS;
	float posYOffset = 0.0f;

	if (!bossUICreated)
	{
		posYOffset = FRAME_POS_Y_INTERVAL * static_cast<float>(characterParam->GetIndex());
	}
	else
	{
		posYOffset = FRAME_POS_Y_INTERVAL * static_cast<float>(characterParam->GetIndex() - 1);
	}

	defaultPos = VAdd(defaultPos, MyMath::VecY(posYOffset));

	if (!characterParam->IsBoss())
	{
		defaultPos = VAdd(defaultPos, MyMath::VecX(FRAME_POS_X_INTERVAL_RESULT));
	}

	// フレーム生成
	std::shared_ptr<GameObject> frameImage = nullptr;

	if (characterParam->IsBoss())
	{
		frameImage = CreateUIImage("Data/UI/BattleScene/BossFrame.png", defaultPos, VGet(1.2f, 1.2f, 1.0f), 0.0f);
	}
	else
	{
		frameImage = CreateUIImage("Data/UI/BattleScene/ChallengerFrame.png", defaultPos, VGet(1.2f, 1.2f, 1.0f), 0.0f);
	}

	characterUI.push_back(frameImage);

	// アイコン生成
	std::shared_ptr<GameObject> iconImage = nullptr;

	VECTOR iconPos = VAdd(defaultPos, ICON_POS_OFFSET);

	switch (characterParam->GetType())
	{
	case CharacterType::KNIGHT:
		iconImage = CreateUIImage("Data/UI/Character/KnightIcon.png", iconPos, VGet(0.6f, 0.6f, 1.0f), 0.0f);
		break;
	case CharacterType::NINJA:
		iconImage = CreateUIImage("Data/UI/Character/NinjaIcon.png", iconPos, VGet(0.6f, 0.6f, 1.0f), 0.0f);
		break;
	case CharacterType::FAIRY:
		iconImage = CreateUIImage("Data/UI/Character/FairyIcon.png", iconPos, VGet(0.6f, 0.6f, 1.0f), 0.0f);
		break;
	case CharacterType::ROBOT:
		iconImage = CreateUIImage("Data/UI/Character/RobotIcon.png", iconPos, VGet(0.6f, 0.6f, 1.0f), 0.0f);
		break;
	case CharacterType::BEAST:
		iconImage = CreateUIImage("Data/UI/Character/BeastIcon.png", iconPos, VGet(0.6f, 0.6f, 1.0f), 0.0f);
		break;
	default:
		break;
	}

	characterUI.push_back(iconImage);

	// 名前生成
	std::shared_ptr<GameObject> nameText = nullptr;

	VECTOR namePos = VAdd(defaultPos, NAME_POS_OFFSET);

	switch (characterParam->GetType())
	{
	case CharacterType::KNIGHT:
		nameText = CreateUIText(namePos, COLOR_BLACK, NAME_BATTLE_SCENE, "Knight");
		break;
	case CharacterType::NINJA:
		nameText = CreateUIText(namePos, COLOR_BLACK, NAME_BATTLE_SCENE, "Ninja");
		break;
	case CharacterType::FAIRY:
		nameText = CreateUIText(namePos, COLOR_BLACK, NAME_BATTLE_SCENE, "Fairy");
		break;
	case CharacterType::ROBOT:
		nameText = CreateUIText(namePos, COLOR_WHITE, NAME_BATTLE_SCENE, "Robot");
		break;
	case CharacterType::BEAST:
		nameText = CreateUIText(namePos, COLOR_WHITE, NAME_BATTLE_SCENE, "Beast");
		break;
	default:
		break;
	}

	characterUI.push_back(nameText);

	return characterUI;
}

/// <summary>
/// ミッションのUI生成
/// </summary>
/// <param name="filePath">画像のファイルパス</param>
/// <returns>UIオブジェクトの配列</returns>
std::vector<std::shared_ptr<GameObject>> RendererManager::CreateMissionUI(const char* filePath)
{
	std::vector<std::shared_ptr<GameObject>> missionUI;

	auto missionGraphObj = std::make_shared<GameObject>();

	std::shared_ptr<GameObject> missionImage = nullptr;

	missionImage = CreateUIImage(filePath, MyMath::Vec2D(1400.0f, 100.0f), VGet(0.7f, 0.7f, 1.0f), 0.0f);

	missionUI.push_back(missionImage);

	std::shared_ptr<GameObject> numText = CreateUIText(MyMath::Vec2D(1400.0f, 100.0f), COLOR_BLACK, NAME_BATTLE_SCENE, "0 / 0");

	missionUI.push_back(numText);

	return missionUI;
}

MyMath::VECTOR_INT RendererManager::GetCurrentIndex()
{
	for (auto& group : m_UIButtonGroups)
	{
		if (auto groupPtr = group.lock())
		{
			if (groupPtr->IsActive())
			{
				return groupPtr->GetCurrentIndex();
			}
		}
	}
	return MyMath::Vec2DInt(0, 0);
}

void RendererManager::CheckCursor(std::shared_ptr<UIInput> input)
{
	for (auto& group : m_UIButtonGroups)
	{
		if (auto groupPtr = group.lock())
		{
			if (groupPtr->IsActive())
			{
				groupPtr->CheckCursor(input);
			}
		}
	}
}

ButtonGroupName RendererManager::GetActiveButtonGroup()
{
	for (auto& group : m_UIButtonGroups)
	{
		if (auto groupPtr = group.lock())
		{
			if (groupPtr->IsActive())
			{
				return groupPtr->GetGroupName();
			}
		}
	}
	return GROUP_NAME_NONE;
}

