#pragma once
#include "../EnemyBase.h"

class Obstacle : public EnemyBase
{
public:
	Obstacle();
	~Obstacle();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

	// ï°êª
	EnemyBase* Clone() override;
	bool CanDestroyByBullet() override { return false; }
	int GetDeathEffectType() override
	{
		return EFFEKSEER_BARRIER;
	}
};