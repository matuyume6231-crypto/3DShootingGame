#pragma once
#include "DxLib.h"

class CollisionAABB;

class Bullet
{
public:
	Bullet();
	~Bullet();

	void Init();
	void Update();
	void Draw();
	void Fin();

	void Shot(VECTOR pos);

	bool IsActive() const { return m_Active; }
	bool IsDead() const { return !m_Active; }
	CollisionAABB* GetAABB() { return m_AABB; }

private:
	VECTOR m_Pos;
	VECTOR m_Velocity;

	bool m_Active;

	int m_Handle;

	CollisionAABB* m_AABB;
};