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

private:
	float m_ShotTimer;
	std::vector<EnemyBullet*> m_Bullets;
	bool m_WaitSecondShot;
	float m_SecondShotTimer;
	int m_SecondLane;
};