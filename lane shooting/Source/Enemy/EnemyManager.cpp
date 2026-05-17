#include "EnemyManager.h"
#include "YellowEnemy/YellowEnemy.h"
#include "Obstacle/Obstacle.h"
#include "Boss/Boss.h"

EnemyManager* EnemyManager::m_Instance = nullptr;

EnemyManager::EnemyManager()
{
	for (int i = 0; i < ENEMY_TYPE_MAX; i++)
	{
		m_OriginalEnemy[i] = nullptr;
	}
}

EnemyManager::~EnemyManager()
{
	Fin();
}

void EnemyManager::Init()
{
	// クローン元のエネミーを生成する
	m_OriginalEnemy[YELLOW_ENEMY] = new YellowEnemy;
	m_OriginalEnemy[OBSTACLE] = new Obstacle;
	m_OriginalEnemy[BOSS_ENEMY] = new Boss;
}

void EnemyManager::Load()
{
	// クローン元のエネミーをロードする
	for (int i = 0; i < ENEMY_TYPE_MAX; i++)
	{
		m_OriginalEnemy[i]->Load();
	}
}

void EnemyManager::Start()
{
	// 範囲for文で安全にリストを回せる
	for (auto enemy : m_EnemyList)
	{
		enemy->Start();
	}
}

void EnemyManager::Step()
{
	// 範囲for文で安全にリストを回せる
	for (auto enemy : m_EnemyList)
	{
		enemy->Step();
	}
}

void EnemyManager::Update()
{
	// 範囲for文で安全にリストを回せる
	for (auto enemy : m_EnemyList)
	{
		enemy->Update();
	}

	// 死亡フラグが立っているエネミーをリストから削除する
	for (auto it = m_EnemyList.begin(); it != m_EnemyList.end(); )
	{
		// 死亡フラグが立っている場合は削除する
		if ((*it)->m_Dead)
		{
			delete* it;
			it = m_EnemyList.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void EnemyManager::Draw()
{
	// 範囲for文で安全にリストを回せる
	for (auto enemy : m_EnemyList)
	{
		enemy->Draw();
	}
}

void EnemyManager::Fin()
{
	// 範囲for文で安全にリストを回せる
	for (auto enemy : m_EnemyList)
	{
		delete enemy;
	}

	// リストをクリア
	m_EnemyList.clear();

	// クローン元も削除する
	for (auto enemy : m_OriginalEnemy)
	{
		delete enemy;
	}
}

EnemyBase* EnemyManager::CreateEnemy(EnemyType type)
{
	// タイプに合わせたエネミーをクローンで生成
	EnemyBase* enemy = m_OriginalEnemy[type]->Clone();

	enemy->Start();

	// 生成したエネミーを管理用リストに追加
	m_EnemyList.push_back(enemy);

	// 返却すれば生成した後にいろいろいじれる
	return enemy;
}
