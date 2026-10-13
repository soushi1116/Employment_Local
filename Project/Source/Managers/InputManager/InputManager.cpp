#include "InputManager.h"
#include "../../Component/Component.h"
#include "../../Component/GameObject.h"
#include "../../Component/AllComponents.h"

InputManager* InputManager::m_Instance = nullptr;

InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

void InputManager::Init()
{

}

void InputManager::Load()
{

}

void InputManager::Start()
{

}

void InputManager::Step()
{

}

void InputManager::Update()
{

}

void InputManager::Draw()
{

}

void InputManager::Fin()
{

}

std::shared_ptr<GameObject> InputManager::CreateUIInput()
{
	auto newInput = std::make_shared<GameObject>();

	auto uiInput = newInput->AddComponent<UIInput>();

	return newInput;
}