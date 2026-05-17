#include "Boss.h"
#include "../../Collision/CollisionManager.h"
#include "../../Collision/CollisionAABB.h"

Boss::Boss()
{
	m_ShotTimer = 0.0f;
}

Boss::~Boss()
{
}

void Boss::Init()
{
}

void Boss::Load()
{
	m_Handle = MV1LoadModel("Data/Enemy/Boss/Boss.x");
}

void Boss::Start()
{
	// AABB
	m_AABB = CollisionManager::GetInstance()->CreateAABB();

	m_AABB->SetTargetPos(&m_Pos);

	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));

	m_AABB->SetSize(VGet(3.0f, 3.0f, 3.0f));

	// ボスは移動しない
	m_Move = VGet(0.0f, 0.0f, 0.0f);

	// HP
	m_HP = 20;

	m_Dead = false;

	m_ShotTimer = 0.0f;
}

void Boss::Step()
{
}

void Boss::Update()
{
	if (m_Dead) return;

	// ボス位置固定
	m_Pos.z = 40.0f;

	// タイマー更新
	m_ShotTimer -= 1.0f / 60.0f;

	if (m_ShotTimer <= 0.0f)
	{
		EnemyBullet* bullet = new EnemyBullet;

		bullet->Init();

		bullet->Shot(m_Pos);

		m_Bullets.push_back(bullet);

		m_ShotTimer = 1.0f;
	}

	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);

	for (auto bullet : m_Bullets)
	{
		bullet->Update();
	}
}

void Boss::Draw()
{
	MV1DrawModel(m_Handle);

	for (auto bullet : m_Bullets)
	{
		bullet->Draw();
	}
}

void Boss::Fin()
{
	for (auto bullet : m_Bullets)
	{
		delete bullet;
	}

	m_Bullets.clear();

	EnemyBase::Fin();
}

EnemyBase* Boss::Clone()
{
	Boss* clone = new Boss;

	clone->m_Dead = false;

	clone->m_Handle = MV1DuplicateModel(m_Handle);

	clone->m_AABB = nullptr;

	return clone;
}