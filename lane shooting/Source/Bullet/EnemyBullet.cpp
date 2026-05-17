#include "EnemyBullet.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"

#define ENEMY_BULLET_SPEED -0.3f

EnemyBullet::EnemyBullet()
{
	m_Active = false;
	m_Handle = 0;
	m_AABB = nullptr;
}

EnemyBullet::~EnemyBullet()
{
	Fin();
}

void EnemyBullet::Init()
{
	m_Handle = MV1LoadModel("Data/Bullet/EnemyBullet.x");

	m_AABB = CollisionManager::GetInstance()->CreateAABB();

	m_AABB->SetTargetPos(&m_Pos);

	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));

	m_AABB->SetSize(VGet(0.7f, 0.7f, 0.7f));
}

void EnemyBullet::Shot(VECTOR pos)
{
	m_Pos = pos;

	m_Velocity = VGet(0.0f, 0.0f, ENEMY_BULLET_SPEED);

	m_Active = true;
}

void EnemyBullet::Update()
{
	if (!m_Active) return;

	m_Pos = VAdd(m_Pos, m_Velocity);

	// ‰æ–ÊŠO
	if (m_Pos.z < -20.0f)
	{
		m_Active = false;
	}
}

void EnemyBullet::Draw()
{
	if (!m_Active) return;

	MV1SetPosition(m_Handle, m_Pos);

	MV1DrawModel(m_Handle);
}

void EnemyBullet::Fin()
{
	if (m_Handle != 0)
	{
		MV1DeleteModel(m_Handle);

		m_Handle = 0;
	}

	m_AABB = nullptr;
}

void EnemyBullet::Destroy()
{
	m_Active = false;
}