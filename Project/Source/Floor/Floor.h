#pragma once
#include "DxLib.h"

class CollisionAABB;

class Floor
{
public:
	Floor();
	~Floor();

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

public:
	VECTOR GetPos() { return m_Pos; }
	CollisionAABB* GetAABB() { return m_AABB; }

private:
	int m_Handle;
	VECTOR m_Pos;
	CollisionAABB* m_AABB;
};