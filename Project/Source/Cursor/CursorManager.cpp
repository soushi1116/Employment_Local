#include "CursorManager.h"

CursorManager* CursorManager::m_Instance = nullptr;

CursorManager::CursorManager()
{
	m_Cursor = nullptr;
}

CursorManager::~CursorManager()
{
	Fin();
}

void CursorManager::CreateCursor(VECTOR pos, VECTOR maxPos, VECTOR minPos, float scale, float diff)
{
	if (!m_Cursor)
	{
		m_Cursor = new Cursor;
		m_Cursor->SetPos(pos);
		m_Cursor->SetMaxPos(maxPos);
		m_Cursor->SetPos(minPos);
		m_Cursor->SetScale(scale);
		m_Cursor->SetMoveDiff(diff);
		m_Cursor->Load();
	}
}

void CursorManager::Init()
{
	if (m_Cursor)
	{
		m_Cursor->Init();
	}
}

void CursorManager::Load()
{
	if (m_Cursor)
	{
		m_Cursor->Load();
	}
}

void CursorManager::Start()
{
	if (m_Cursor)
	{
		m_Cursor->Start();
	}
}

void CursorManager::Step()
{
	if (m_Cursor)
	{
		m_Cursor->Step();
	}
}

void CursorManager::Update()
{
	if (m_Cursor)
	{
		m_Cursor->Update();
	}
}

void CursorManager::Draw()
{
	if (m_Cursor)
	{
		m_Cursor->Draw();
	}
}

void CursorManager::Fin()
{
	m_Cursor->Fin();
}


