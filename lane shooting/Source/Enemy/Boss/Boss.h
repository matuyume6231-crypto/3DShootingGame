#pragma once
#include "../EnemyBase.h"
#include "../../Bullet/EnemyBullet.h"
#include <vector>

class Boss : public EnemyBase
{
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
private:
	float m_ShotTimer;
	std::vector<EnemyBullet*> m_Bullets;
	bool m_WaitSecondShot;// 2発目の弾を撃つために待機するフラグ
	float m_SecondShotTimer; // 2発目の弾を撃つまでのタイマー
	int m_SecondLane;// 2発目の弾を撃つレーン

	bool m_DamageFlash;// ダメージを受けたときに点滅させるフラグ
	float m_DamageFlashTimer; // 点滅のタイマー
};