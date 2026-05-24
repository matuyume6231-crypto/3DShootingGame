#pragma once
#include "../EnemyBase.h"
#include "../../Bullet/EnemyBullet.h"
#include <vector>

class Boss : public EnemyBase
{
public:
	enum BossState
	{
		BOSS_NORMAL,       // 通常状態
		BOSS_DYING,        // ダメージを受けている状態
		BOSS_DEAD,         // 完全に消えた状態
	};

public:
	Boss();
	~Boss();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;

	EnemyBase* Clone() override;

	std::vector<EnemyBullet*>& GetBullets()
	{
		return m_Bullets;
	}
	void Damage(int damage) override;
	void UpdateDeath();
	bool IsDeathFinished() const
	{
		return m_State == BOSS_DEAD;
	}

private:
	float m_ShotTimer;
	std::vector<EnemyBullet*> m_Bullets;
	bool m_WaitSecondShot;// 2発目の弾を撃つために待機するフラグ
	float m_SecondShotTimer; // 2発目の弾を撃つまでのタイマー
	int m_SecondLane;// 2発目の弾を撃つレーン

	bool m_DamageFlash;// ダメージを受けたときに点滅させるフラグ
	float m_DamageFlashTimer; // 点滅のタイマー

	BossState m_State;  // ボスの状態管理
	float m_DeathTimer; // 死亡状態から完全に消えるまでのタイマー
	float m_ShakeTimer; // ダメージを受けたときの画面揺れのタイマー
	bool m_DeathEffectPlayed; // 死亡エフェクトを一度だけ再生するためのフラグ
	float m_HideTimer; // エフェクト再生後にモデルを消すまでのタイマー
	bool m_Hidden; // モデルが非表示になっているかどうか
};