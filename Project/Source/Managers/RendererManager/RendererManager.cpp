#include "RendererManager.h"
#include "../../Component/Component.h"
#include "../../Component/GameObject.h"
#include "../../Component/AllComponents.h"

RendererManager* RendererManager::m_Instance = nullptr;

RendererManager::RendererManager()
{
	
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
	auto backGround = std::make_shared<GameObject>();

	auto backGroundRenderer = backGround->AddComponent<BackGroundRenderer>(filePath);

	return backGround;
}