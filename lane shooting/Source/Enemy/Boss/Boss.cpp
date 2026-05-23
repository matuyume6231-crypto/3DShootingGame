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

	m_WaitSecondShot = false;

	m_SecondShotTimer = 0.0f;

	m_SecondLane = 0;
}

void Boss::Step()
{
}

void Boss::Update()
{
	if (m_Dead) return;

	// ボス位置固定
	m_Pos.z = 40.0f;

	// 2発目の弾のタイマー更新
	if (m_WaitSecondShot)
	{
		m_SecondShotTimer -= 1.0f / 60.0f;

		if (m_SecondShotTimer <= 0.0f)
		{
			EnemyBullet* bullet = new EnemyBullet;

			bullet->Init();

			VECTOR shotPos = m_Pos;

			shotPos.x = m_LanePos[m_SecondLane];

			bullet->Shot(shotPos);

			m_Bullets.push_back(bullet);

			m_WaitSecondShot = false;
		}
	}

	// タイマー更新
	m_ShotTimer -= 1.0f / 60.0f;

	if (m_ShotTimer <= 0.0f)
	{
		// 1～2発ランダム
		int shotCount = rand() % 2 + 1;

		// 2発目ディレイするか
		bool delayShot = (rand() % 2 == 0);

		// 使用済みレーン管理
		bool usedLane[3] = { false,false,false };

		for (int i = 0; i < shotCount; i++)
		{
			int lane = 0;

			// do-while文
			// 普通のwhileは条件が最初から満たされていないとループに入らないが、
			// do-whileは一度は必ずループに入る
			// 未使用レーンを選ぶ
			do
			{
				lane = rand() % 3;
			} 
			while (usedLane[lane]);

			usedLane[lane] = true;

			if (shotCount == 2 &&
				i == 1 &&
				delayShot)
			{
				m_WaitSecondShot = true;

				m_SecondShotTimer = 0.3f;

				m_SecondLane = lane;
			}
			else
			{
				EnemyBullet* bullet = new EnemyBullet;

				bullet->Init();

				VECTOR shotPos = m_Pos;

				shotPos.x = m_LanePos[lane];

				bullet->Shot(shotPos);

				m_Bullets.push_back(bullet);
			}
		}

		m_ShotTimer = 1.0f;
	}

	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);

	for (auto bullet : m_Bullets)
	{
		bullet->Update();
	}

	if (m_DamageFlash)
	{
		m_DamageFlashTimer -= 1.0f / 60.0f;

		if (m_DamageFlashTimer <= 0)
		{
			m_DamageFlash = false;
		}
	}
}

void Boss::Draw()
{
	MV1DrawModel(m_Handle);

	for (auto bullet : m_Bullets)
	{
		bullet->Draw();
	}

	if (m_DamageFlash)
	{
		MV1SetDifColorScale(
			m_Handle,
			GetColorF(1.0f, 0.3f, 0.3f, 1.0f)
		);
	}
	else
	{
		MV1SetDifColorScale(
			m_Handle,
			GetColorF(1, 1, 1, 1)
		);
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

void Boss::Damage(int damage)
{
	EnemyBase::Damage(damage);

	if (!m_DamageFlash)
	{
		m_DamageFlash = true;
		m_DamageFlashTimer = 0.1f;
	}
}