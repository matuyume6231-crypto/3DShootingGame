#pragma once
#include <vector>
#include "../Enemy/EnemyManager.h"

struct SpawnData
{
	float time;      // 何秒後に出すか
	EnemyType type;  // 敵タイプ
	int lane;        // レーン（0,1,2）
};

class EnemySpawnManager
{
public:
	EnemySpawnManager();
	~EnemySpawnManager();

	void Init();
	void Update(float deltaTime);

private:
	float m_Timer;

	std::vector<SpawnData> m_SpawnList;
	int m_NextIndex;
};