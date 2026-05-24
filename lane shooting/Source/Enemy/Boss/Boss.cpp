#include "Boss.h"
#include "../../Collision/CollisionManager.h"
#include "../../Collision/CollisionAABB.h"
#include "../../MyEffekseer/EffekseerManager.h"
#include "../../Camera/CameraManager.h"
#include "../../Camera/CameraDead.h"
#include "../../Sound/SoundManager.h"

Boss::Boss()
{
	m_ShotTimer = 0.0f;
}

Boss::~Boss()
{
}

void Boss::Init()
{
}

void Boss::Load()
{
	m_Handle = MV1LoadModel("Data/Enemy/Boss/Boss.x");
}

void Boss::Start()
{
	// AABB
	m_AABB = CollisionManager::GetInstance()->CreateAABB();

	m_AABB->SetTargetPos(&m_Pos);

	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));

	m_AABB->SetSize(VGet(3.0f, 3.0f, 3.0f));

	// ボスは移動しない
	m_Move = VGet(0.0f, 0.0f, 0.0f);

	// HP
	m_HP = 20;
	m_Dead = false;
	m_ShotTimer = 0.0f;
	m_WaitSecondShot = false;
	m_SecondShotTimer = 0.0f;
	m_SecondLane = 0;

	m_State = BOSS_NORMAL;
	m_DeathTimer = 0.0f;
	m_ShakeTimer = 0.0f;
	m_DeathEffectPlayed = false;

	m_DamageFlash = false;
	m_DamageFlashTimer = 0.0f;

	m_HideTimer = 0.0f;
	m_Hidden = false;

	// 初期位置セットしないと(0,0,0)で一瞬表示されてしまうから、初期位置セットしておく
	MV1SetPosition(m_Handle, m_Pos);
}

void Boss::Step()
{
}

void Boss::Update()
{
	// 死亡演出中
	if (m_State == BOSS_DYING)
	{
		UpdateDeath();
		return;
	}

	if (m_State == BOSS_DEAD)
		return;

	// ボス位置固定
	m_Pos.z = 40.0f;

	// 2発目の弾のタイマー更新
	if (m_WaitSecondShot)
	{
		m_SecondShotTimer -= 1.0f / 60.0f;

		if (m_SecondShotTimer <= 0.0f)
		{
			EnemyBullet* bullet = new EnemyBullet;

			bullet->Init();

			VECTOR shotPos = m_Pos;

			shotPos.x = m_LanePos[m_SecondLane];

			bullet->Shot(shotPos);

			m_Bullets.push_back(bullet);

			m_WaitSecondShot = false;
		}
	}

	// タイマー更新
	m_ShotTimer -= 1.0f / 60.0f;

	if (m_ShotTimer <= 0.0f)
	{
		// 1～2発ランダム
		int shotCount = rand() % 2 + 1;

		// 2発目ディレイするか
		bool delayShot = (rand() % 2 == 0);

		// 使用済みレーン管理
		bool usedLane[3] = { false,false,false };

		for (int i = 0; i < shotCount; i++)
		{
			int lane = 0;

			// do-while文
			// 普通のwhileは条件が最初から満たされていないとループに入らないが、
			// do-whileは一度は必ずループに入る
			// 未使用レーンを選ぶ
			do
			{
				lane = rand() % 3;
			} 
			while (usedLane[lane]);

			usedLane[lane] = true;

			if (shotCount == 2 &&
				i == 1 &&
				delayShot)
			{
				m_WaitSecondShot = true;

				m_SecondShotTimer = 0.3f;

				m_SecondLane = lane;
			}
			else
			{
				EnemyBullet* bullet = new EnemyBullet;

				bullet->Init();

				VECTOR shotPos = m_Pos;

				shotPos.x = m_LanePos[lane];

				bullet->Shot(shotPos);

				m_Bullets.push_back(bullet);
			}
		}

		m_ShotTimer = 1.0f;
	}

	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);

	for (auto bullet : m_Bullets)
	{
		bullet->Update();
	}

	if (m_DamageFlash)
	{
		m_DamageFlashTimer -= 1.0f / 60.0f;

		if (m_DamageFlashTimer <= 0)
		{
			m_DamageFlash = false;
		}
	}
}

void Boss::UpdateDeath()
{
	m_DeathTimer -= 1.0f / 60.0f;
	m_ShakeTimer -= 1.0f / 60.0f;

	// 揺れ
	if (m_ShakeTimer > 0.0f)
	{
		float offset =
			((rand() % 100) / 100.0f - 0.5f) * 0.8f;

		VECTOR pos = m_Pos;
		pos.x += offset;

		MV1SetPosition(m_Handle, pos);
	}

	// 爆発（1回だけ）
	if (!m_DeathEffectPlayed && m_ShakeTimer <= 0.0f)
	{
		EffekseerManager::GetInstance()->PlayEffect(
			EFFEKSEER_BOSSDEAD,
			m_Pos
		);

		SoundManager::GetInstance()->PlayFocusSE();

		m_DeathEffectPlayed = true;

		// 約220フレーム待機
		m_HideTimer = 220.0f / 60.0f;
	}

	if (m_DeathEffectPlayed && !m_Hidden)
	{
		m_HideTimer -= 1.0f / 60.0f;

		if (m_HideTimer <= 0.0f)
		{
			// 爆発SE
			SoundManager::GetInstance()->PlayBombSE();
			MV1SetVisible(m_Handle, FALSE);
			m_Hidden = true;
		}
	}

	// 終了
	if (m_DeathTimer <= 0.0f)
	{
		m_State = BOSS_DEAD;
	}
}

void Boss::Draw()
{
	MV1DrawModel(m_Handle);

	for (auto bullet : m_Bullets)
	{
		bullet->Draw();
	}

	if (m_DamageFlash)
	{
		MV1SetDifColorScale(
			m_Handle,
			GetColorF(1.0f, 0.3f, 0.3f, 1.0f)
		);
	}
	else
	{
		MV1SetDifColorScale(
			m_Handle,
			GetColorF(1, 1, 1, 1)
		);
	}
}

void Boss::Fin()
{
	for (auto bullet : m_Bullets)
	{
		delete bullet;
	}

	m_Bullets.clear();

	EnemyBase::Fin();
}

EnemyBase* Boss::Clone()
{
	Boss* clone = new Boss;

	clone->m_Dead = false;

	clone->m_Handle = MV1DuplicateModel(m_Handle);

	clone->m_AABB = nullptr;

	return clone;
}

void Boss::Damage(int damage)
{
	if (m_State != BOSS_NORMAL)
	{
		return;
	}

	m_HP -= damage;

	if (!m_DamageFlash)
	{
		m_DamageFlash = true;
		m_DamageFlashTimer = 0.1f;
	}

	if (m_HP <= 0)
	{
		m_HP = 0;

		// 残っているボス弾を消す
		for (auto bullet : m_Bullets)
		{
			bullet->Destroy();
		}

		m_State = BOSS_DYING;

		// BGM停止
		SoundManager::GetInstance()->StopBGM();

		// 演出時間（8秒エフェクト想定）
		m_DeathTimer = 9.0f;

		// 揺れ時間（先に少し演出）
		m_ShakeTimer = 0.7f;


		m_DeathEffectPlayed = false;

		// カメラ切替
		CameraManager* cameraManager = CameraManager::GetInstance();

		cameraManager->CreateCamera(CAMERA_BOSS_DEATH);

		CameraDead* camera =
			dynamic_cast<CameraDead*>(cameraManager->GetCamera(CAMERA_BOSS_DEATH));

		if (camera)
		{
			camera->SetBoss(this);
		}

		cameraManager->SetActiveCamera(CAMERA_BOSS_DEATH);
	}
}