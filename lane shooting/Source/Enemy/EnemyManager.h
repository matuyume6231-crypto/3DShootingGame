#pragma once
#include "EnemyBase.h"
#include <list>

enum EnemyType
{
	YELLOW_ENEMY,
	OBSTACLE,
	ENEMY_TYPE_MAX,
	ENEMY_TYPE_NONE = -1
};

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

public:
	static void CreateInstance() { if (!m_Instance) m_Instance = new EnemyManager; }
	static EnemyManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance)delete m_Instance; m_Instance = nullptr; }

public:
	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

public:
	EnemyBase* CreateEnemy(EnemyType type);
	std::list<EnemyBase*>& GetEnemyList() { return m_EnemyList; }
private:
	static EnemyManager* m_Instance;

	// クローン元のエネミーを管理する配列
	EnemyBase* m_OriginalEnemy[ENEMY_TYPE_MAX];

	// C++標準ライブラリのリストクラス
	std::list<EnemyBase*> m_EnemyList;
};
