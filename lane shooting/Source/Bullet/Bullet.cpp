#include "Bullet.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"

#define BULLET_SPEED 0.5f

Bullet::Bullet()
{
	m_Active = false;
	m_Handle = 0;
	m_AABB = nullptr;
}

Bullet::~Bullet()
{
	Fin();
}

void Bullet::Init()
{
	m_Handle = MV1LoadModel("Data/Bullet/Bullet.x");

	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_AABB->SetSize(VGet(0.5f, 0.5f, 0.5f));
}

void Bullet::Shot(VECTOR pos)
{
	m_Pos = pos;
	m_Velocity = VGet(0.0f, 0.0f, BULLET_SPEED);
	m_Active = true;
}

void Bullet::Update()
{
	if (!m_Active) return;

	// 前に進む
	m_Pos = VAdd(m_Pos, m_Velocity);

	// 画面外チェック
	if (m_Pos.z > 50.0f)
	{
		m_Active = false;
	}
}

void Bullet::Draw()
{
	if (!m_Active) return;

	MV1SetPosition(m_Handle, m_Pos);
	MV1DrawModel(m_Handle);
}

void Bullet::Fin()
{
	if (m_Handle != 0)
	{
		MV1DeleteModel(m_Handle);
		m_Handle = 0;
	}
	m_AABB = nullptr;
}