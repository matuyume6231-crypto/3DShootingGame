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

	// ウェーブ設計
	m_SpawnList =
	{
		{2.0f, YELLOW_ENEMY, 0, -0.1},
		{2.0f, YELLOW_ENEMY, 2, -0.2},
		{4.0f, YELLOW_ENEMY, 1, -0.1},
		{6.0f, YELLOW_ENEMY, 2, -0.1},
		{5.0f, OBSTACLE, 0, -0.15f},
		{5.0f, OBSTACLE, 1, -0.15f},
		{8.0f, YELLOW_ENEMY, 2, -0.2},
		{9.0f, OBSTACLE, 0, -0.2f},
		{11.0f, YELLOW_ENEMY, 0, -0.2},
		{10.0f, YELLOW_ENEMY, 2, -0.2},
		{12.0f, OBSTACLE, 1, -0.25f},
		{12.0f, OBSTACLE, 2, -0.25f},
		{15.0f, YELLOW_ENEMY, 0, -0.3f},
		{16.0f, YELLOW_ENEMY, 0, -0.3f},
		{17.0f, YELLOW_ENEMY, 0, -0.3f},
		{17.0f, YELLOW_ENEMY, 2, -0.3f},
		{18.0f, YELLOW_ENEMY, 1, -0.3f},
		{20.0f, YELLOW_ENEMY, 2, -0.3f},
		{22.0f, OBSTACLE, 1, -0.35f},
		{22.0f, YELLOW_ENEMY, 2, -0.35f},
		{23.0f, YELLOW_ENEMY, 0, -0.35f},
		{25.0f, YELLOW_ENEMY, 0, -0.4f},
		{28.0f, YELLOW_ENEMY, 1, -0.4f},
		{29.0f, YELLOW_ENEMY, 2, -0.4f},
		{30.0f, BOSS_ENEMY, 1, 0.0f},
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

			float lanePos[3] = { -10.0f, 0.0f, 10.0f };

			VECTOR spawnPos;

			if (data.type == BOSS_ENEMY)
			{
				spawnPos = VGet(0.0f, 0.0f, 40.0f);
			}
			else
			{
				spawnPos = VGet(
					lanePos[data.lane],
					0.0f,
					50.0f
				);
			}

			EnemyBase* enemy =
				EnemyManager::GetInstance()->CreateEnemy(
					data.type,
					data.lane,
					spawnPos
				);

			enemy->SetMoveSpeed(data.moveSpeed);
			m_NextIndex++;
		}
		else
		{
			break;
		}
	}
}