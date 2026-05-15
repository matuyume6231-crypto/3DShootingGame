#pragma once
#include "DxLib.h"

class CollisionAABB;

class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

public:
	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start() = 0;
	virtual void Step() = 0;

	// 各エネミー専用で処理を作る必要がない場合は基底クラスで共通処理にする
	virtual void Update();
	virtual void Draw();
	virtual void Fin();

	// 複製、量産するためのクローン関数
	virtual EnemyBase* Clone() = 0;

public:

	void SetPos(VECTOR pos) { m_Pos = pos; }
	bool m_Dead; // 死亡フラグ
	CollisionAABB* GetAABB() { return m_AABB; }

	
public:
	void SetLane(int lane) { m_Lane = lane; }
	int GetLane() const { return m_Lane; }

protected:
	int m_Handle;
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Move;   // 移動速度
	// 追加
	int m_Lane;
	float m_LanePos[3];

	CollisionAABB* m_AABB;
};


