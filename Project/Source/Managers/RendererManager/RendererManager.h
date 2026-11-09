#pragma once
#include "DxLib.h"
#include <vector>
#include <list>
#include <string>
#include <memory>
#include "../../MyMath/MyMath.h"
#include "../../Input/InputParameter.h"
#include "../../Component/Renderer/UIButtonGroup.h"
#include "../Singleton.h"

class GameObject;
class UIButtonGroup;
class Component;

enum FontHandleType
{
	TIMER_TEXT,
	NAME_BATTLE_SCENE,
	NAME_RESULT_SCENE,
	MISSION_TEXT,
	FONT_HANDLE_MAX,
	FONT_HANDLE_NONE = -1
};

class RendererManager : public Singleton<RendererManager>
{
public:
	RendererManager();
	~RendererManager();	

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

	void CheckCursor(std::shared_ptr<UIInput> input);

	std::shared_ptr<GameObject> CreateBackGround(const char* filePath);
	std::shared_ptr<GameObject> CreateUIImage(const char* filePath, VECTOR pos, VECTOR exRate, float angle);
	std::shared_ptr<GameObject> CreateUIButton(const char* filePath, VECTOR pos, VECTOR exRate, float angle, MyMath::VECTOR_INT index, std::weak_ptr<UIButtonGroup> parent);
	std::shared_ptr<GameObject> CreateUIText(VECTOR pos, unsigned int color, FontHandleType type, const char* text);
	std::shared_ptr<GameObject> CreateButtonGroup(ButtonGroupName name);
	std::vector<std::shared_ptr<GameObject>> CreateCharacterBattleUI(std::shared_ptr<CharacterParameter> characterParam);
	std::vector<std::shared_ptr<GameObject>> CreateCharacterResultUI(std::shared_ptr<CharacterParameter> characterParam, bool bossUICreated);
	std::vector<std::shared_ptr<GameObject>> CreateMissionUI(const char* filePath);

	MyMath::VECTOR_INT GetCurrentIndex();

	ButtonGroupName GetActiveButtonGroup();

	std::vector<std::weak_ptr<UIButtonGroup>> GetButtonGroups() { return m_UIButtonGroups; }

	int GetFontHandle(FontHandleType type) const { return m_FontHandle[type]; }

private:
	static RendererManager* m_Instance;
	
	std::vector<std::weak_ptr<UIButtonGroup>> m_UIButtonGroups;

	int m_FontHandle[FONT_HANDLE_MAX];
};