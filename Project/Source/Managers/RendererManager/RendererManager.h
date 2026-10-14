#pragma once
#include "DxLib.h"
#include <vector>
#include <list>
#include <string>
#include <memory>
#include "../../MyMath/MyMath.h"
#include "../../Input/InputParameter.h"
#include "../../Component/Renderer/UIButtonGroup.h"

class GameObject;
class UIButtonGroup;

class RendererManager
{
public:
	RendererManager();
	~RendererManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new RendererManager;
		}
	}

	static RendererManager* GetInstance() { return m_Instance; }

	static void DeleteInstance()
	{
		if (m_Instance)
		{
			delete m_Instance;
			m_Instance = nullptr;
		}
	}

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
	std::shared_ptr<GameObject> CreateUIImage(const char* filePath, VECTOR pos, float exRate, float angle);
	std::shared_ptr<GameObject> CreateUIButton(const char* filePath, VECTOR pos, float exRate, float angle, MyMath::VECTOR_INT index, std::shared_ptr<UIButtonGroup> parent);
	std::shared_ptr<GameObject> CreateUIText();
	std::shared_ptr<GameObject> CreateButtonGroup(ButtonGroupName name);

	MyMath::VECTOR_INT GetCurrentIndex();

	ButtonGroupName GetActiveButtonGroup();

	std::vector<std::shared_ptr<UIButtonGroup>> GetButtonGroups() { return m_UIButtonGroups; }

private:
	static RendererManager* m_Instance;
	
	std::vector<std::shared_ptr<UIButtonGroup>> m_UIButtonGroups;
};