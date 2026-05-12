#pragma once
#include "../EnemyBase.h"

class YellowEnemy : public EnemyBase
{
public:
	YellowEnemy();
	~YellowEnemy();

public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

	// Update, Draw, FinはEnemyBaseの処理で十分なので不要

	// 複製、量産するためのクローン関数
	EnemyBase* Clone() override;
};
