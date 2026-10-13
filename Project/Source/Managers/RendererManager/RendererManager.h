#pragma once
#include "DxLib.h"
#include <vector>
#include <list>
#include <string>
#include <memory>
#include "../../MyMath/MyMath.h"
#include "../../Input/InputParameter.h"

class GameObject;
class UIButton;
class UIInput;

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
	std::shared_ptr<GameObject> CreateUIButton(const char* filePath, VECTOR pos, float exRate, float angle, MyMath::VECTOR_INT index);
	std::shared_ptr<GameObject> CreateUIText();

	void SetTotalIndex(MyMath::VECTOR_INT index) { m_TotalIndex = index; }
	MyMath::VECTOR_INT GetCurrentIndex() { return m_CurrentIndex; }

private:
	static RendererManager* m_Instance;
	MyMath::VECTOR_INT m_TotalIndex;
	MyMath::VECTOR_INT m_CurrentIndex;

	std::vector<std::shared_ptr<UIButton>> m_UIButtons;
};