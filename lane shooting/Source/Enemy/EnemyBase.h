#pragma once
#include "DxLib.h"
#include "../MyEffekseer/EffekseerParam.h"

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
	// 速度設定関数
	void SetMoveSpeed(float speed);
	// 弾で破壊できるか
	virtual bool CanDestroyByBullet() { return true; }
public:

	void SetPos(VECTOR pos) { m_Pos = pos; }
	VECTOR GetPos() const { return m_Pos; }
	bool m_Dead; // 死亡フラグ
	CollisionAABB* GetAABB() { return m_AABB; }
	virtual int GetDeathEffectType()
	{
		return EFFEKSEER_HIT;
	}

public:
	void SetLane(int lane) { m_Lane = lane; }
	int GetLane() const { return m_Lane; }

public:
	virtual void Damage(int damage);

	int GetHP() const { return m_HP; }
	bool IsDead() const { return m_Dead; }

protected:
	int m_Handle;
	int m_HP;
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Move;   // 移動速度
	// レーン管理用の変数
	int m_Lane;
	float m_LanePos[3];

	CollisionAABB* m_AABB;
};