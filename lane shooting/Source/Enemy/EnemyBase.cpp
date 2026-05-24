#include "EnemyBase.h"
#include "../MyMath/MyMath.h"

EnemyBase::EnemyBase()
{
	m_Handle = 0;
	m_Pos = VGet(0.0f, 0.0f, -10.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0f, 0.0f, -0.1f); // 手前方向(-Z)に進む
	m_AABB = nullptr;
	m_Dead = false;
	m_HP = 1;
	// レーン初期化
	m_Lane = 1;
	m_LanePos[0] = -10.0f;
	m_LanePos[1] = 0.0f;
	m_LanePos[2] = 10.0f;
}

EnemyBase::~EnemyBase()
{
	Fin();
}

void EnemyBase::Update()
{
	if (m_Dead) return;

	// レーン位置反映
	m_Pos.x = m_LanePos[m_Lane];

	// 前進
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);

	// 画面外で死亡
	if (m_Pos.z < -10.0f) // ※カメラ位置に合わせて調整します
	{
		m_Dead = true;
		return;
	}

	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
}

void EnemyBase::Draw()
{
	MV1DrawModel(m_Handle);
}

void EnemyBase::Fin()
{
	if (m_Handle != 0)
	{
		MV1DeleteModel(m_Handle);
		m_Handle = 0;
	}
}

void EnemyBase::SetMoveSpeed(float speed)
{
	m_Move.z = speed;
}

void EnemyBase::Damage(int damage)
{
	if (m_Dead) return;

	m_HP -= damage;

	if (m_HP <= 0)
	{
		m_HP = 0;
		m_Dead = true;
	}
}