#include "EnemySpawnManager.h"
#include "../Enemy/EnemyManager.h"
#include "../Enemy/EnemyBase.h"

EnemySpawnManager::EnemySpawnManager()
{
	m_Timer = 0.0f;
	m_NextIndex = 0;
}


EnemySpawnManager::~EnemySpawnManager()
{
}

void EnemySpawnManager::Init()
{
	m_Timer = 0.0f;
	m_NextIndex = 0;

	// ウェーブ設計（ここが重要）
	m_SpawnList =
	{
		{2.0f, YELLOW_ENEMY, 0},
		{4.0f, YELLOW_ENEMY, 1},
		{6.0f, YELLOW_ENEMY, 2},
		{8.0f, YELLOW_ENEMY, 1},
	};
}

void EnemySpawnManager::Update(float deltaTime)
{
	m_Timer += deltaTime;

	while (m_NextIndex < m_SpawnList.size())
	{
		if (m_Timer >= m_SpawnList[m_NextIndex].time)
		{
			const SpawnData& data = m_SpawnList[m_NextIndex];

			EnemyBase* enemy =
				EnemyManager::GetInstance()->CreateEnemy(data.type);

			float lanePos[3] = { -10.0f, 0.0f, 10.0f };

			enemy->SetLane(data.lane);
			enemy->SetPos(VGet(lanePos[data.lane], 0.0f, 50.0f));

			m_NextIndex++;
		}
		else
		{
			break;
		}
	}
}