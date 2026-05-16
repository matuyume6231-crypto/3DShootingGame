#include "Obstacle.h"
#include "../../Collision/CollisionManager.h"
#include "../../Collision/CollisionAABB.h"

Obstacle::Obstacle()
{
}

Obstacle::~Obstacle()
{
}

void Obstacle::Init()
{
}

void Obstacle::Load()
{
	// 障害物モデル
	m_Handle = MV1LoadModel("Data/Enemy/Obstacle/Obstacle.x");
}

void Obstacle::Start()
{
	// AABB生成
	m_AABB = CollisionManager::GetInstance()->CreateAABB();

	m_AABB->SetTargetPos(&m_Pos);

	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));

	// 少し大きめでも良い
	m_AABB->SetSize(VGet(1.5f, 1.5f, 1.5f));

	// 前進速度
	m_Move = VGet(0.0f, 0.0f, -0.1f);

	m_Dead = false;
}

void Obstacle::Step()
{
}

EnemyBase* Obstacle::Clone()
{
	Obstacle* clone = new Obstacle;

	clone->m_Dead = false;

	// モデル複製
	clone->m_Handle = MV1DuplicateModel(m_Handle);

	clone->m_AABB = nullptr;

	return clone;
}