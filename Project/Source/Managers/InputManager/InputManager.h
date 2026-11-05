#pragma once
#include "DxLib.h"
#include <vector>
#include <list>
#include <string>
#include <memory>
#include "../Singleton.h"

class GameObject;

class InputManager : public Singleton<InputManager>
{
public:
	InputManager();
	~InputManager();

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

	std::shared_ptr<GameObject> CreateUIInput();

private:
	static InputManager* m_Instance;
	
};