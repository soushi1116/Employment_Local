#pragma once
#include "Cursor.h"

class CursorManager
{
public:
	CursorManager();
	~CursorManager();

public:
	static void CreateInstance()
	{
		if (!m_Instance)
		{
			m_Instance = new CursorManager;
		}
	}

	static CursorManager* GetInstance() { return m_Instance; }

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

public:
	void CreateCursor(VECTOR pos, VECTOR maxPos, VECTOR minPos, float scale, float diff);

	Cursor* GetCursor() { return m_Cursor; }

private:
	static CursorManager* m_Instance;

	Cursor* m_Cursor;
};

