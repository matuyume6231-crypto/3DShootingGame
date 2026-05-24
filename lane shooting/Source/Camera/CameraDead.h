#pragma once
#include "CameraBase.h"

class EenemyBase;
class Boss;

// ボス死亡演出用カメラ
class CameraDead : public CameraBase
{
public:
	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;

public:
	void SetBoss(Boss* boss) { m_Boss = boss; }
	bool IsFinished() const { return m_Finished; }

private:
	Boss* m_Boss;

	float m_Time;
	bool m_Finished;
};