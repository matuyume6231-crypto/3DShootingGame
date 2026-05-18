#include "DxLib.h"
#include "Play.h"
#include "../../Player/Player.h"
#include "../../Player/PlayerManager.h"
#include "../../Camera/CameraManager.h"
#include "../../Input/Input.h"
#include "../../Collision/CollisionManager.h"
#include "../../Bullet/Bullet.h"
#include "../../Enemy/EnemyManager.h"
#include "../../Collision/CollisionParameter.h"
#include "../../Collision/CollisionAABB.h"
#include "../../Enemy/EnemySpawnManager.h"
#include "../SceneManager.h"
#include "../../Enemy/Boss/Boss.h"
#include "../../Skybox/Skybox.h"

PlayScene::PlayScene() : SceneBase()
{
	m_Skybox = nullptr;
}

PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
	// コリジョン
	CollisionManager::CreateInstance();

	// プレイヤー
	PlayerManager::CreateInstance();
	PlayerManager::GetInstance()->CreatePlayer();

	// カメラ
	CameraManager::CreateInstance();
	CameraManager* camera = CameraManager::GetInstance();
	camera->CreateCamera(CAMERA);

	// 弾初期化
	m_ShotTimer = 0.0f;

	// 床
	//m_Stage = new Stage;

	// 天球生成
	m_Skybox = new Skybox;

	// ブロック
	//BlockManager::CreateInstance();
	//BlockManager::GetInstance()->Init();

	// 敵
	EnemyManager::CreateInstance();
	EnemyManager::GetInstance()->Init();
	m_SpawnManager = new EnemySpawnManager;
	m_SpawnManager->Init();
}

void PlayScene::Load()
{
	PlayerManager::GetInstance()->Load();
	CameraManager::GetInstance()->Load();
	EnemyManager::GetInstance()->Load();

	//m_Stage->Load();
	// 天球をロード
	m_Skybox->Load("Data/Skybox/Skybox.x");
}

void PlayScene::Start()
{
	PlayerManager::GetInstance()->Start();
	CameraManager::GetInstance()->Start();
	EnemyManager::GetInstance()->Start();

	//m_Stage->Start();
}

void PlayScene::Step()
{
	CameraManager* camera = CameraManager::GetInstance();

	PlayerManager::GetInstance()->Step();
	EnemyManager::GetInstance()->Step();
	camera->Step();
	//m_Stage->Step();
	//BlockManager::GetInstance()->Step();
	// 天球ステップ
	m_Skybox->Step();

	// クールタイム更新
	if (m_ShotTimer > 0.0f)
	{
		m_ShotTimer -= 1.0f / 60.0f; // 60FPS想定
	}

	// Zキーで発射
	if (Input::IsTriggerKey(Input::KEY_Z))
	{
		if (m_ShotTimer <= 0.0f)
		{
			Bullet* bullet = new Bullet;
			bullet->Init();

			// プレイヤー位置取得
			Player* player = PlayerManager::GetInstance()->GetPlayer();

			VECTOR pos = player->GetPos();
			bullet->Shot(pos);

			m_Bullets.push_back(bullet);

			m_ShotTimer = SHOT_COOLDOWN;
		}
	}
}

void PlayScene::Update()
{
	CameraManager* camera = CameraManager::GetInstance();

	PlayerManager::GetInstance()->Update();

	Player* player = PlayerManager::GetInstance()->GetPlayer();

	if (player->IsDead())
	{
		SceneManager::GetInstance()->ChangeScene(OVER);
		return;
	}

	// ボスが全滅してたらクリア
	auto& enemies = EnemyManager::GetInstance()->GetEnemyList();
	for (auto enemy : enemies)
	{
		Boss* boss = dynamic_cast<Boss*>(enemy);

		if (boss && boss->IsDead())
		{
			SceneManager::GetInstance()->ChangeScene(CLEAR);

			return;
		}
	}

	EnemyManager::GetInstance()->Update();
	m_SpawnManager->Update(1.0f / 60.0f);
	camera->Update();
	// 天球更新
	m_Skybox->Update();
	//m_Stage->Update();
	//BlockManager::GetInstance()->Update();
	
	// 弾更新
	for (auto bullet : m_Bullets)
	{
		bullet->Update();
	}

	for (auto bullet : m_Bullets)
	{
		if (!bullet->IsActive()) continue;

		for (auto enemy : enemies)
		{
			if (enemy->m_Dead) continue;

			if (bullet->GetAABB() && enemy->GetAABB())
			{
				HitResultAABB result =
					bullet->GetAABB()->CheckAABB(enemy->GetAABB());

				if (result.isHit)
				{
					// 弾を消す
					bullet->Fin();
					bullet->Destroy();

					// 敵を消す(一部敵は消えない)
					if (enemy->CanDestroyByBullet())
					{
						enemy->Damage(1);
					}
					break; // この弾は終了
				}
			}
		}
	}

	// プレイヤー死亡済みならスキップ
	if (!player->IsDead())
	{
		for (auto enemy : enemies)
		{
			// 敵死亡済みならスキップ
			if (enemy->m_Dead) continue;

			// 当たり判定存在チェック
			if (player->GetAABB() && enemy->GetAABB())
			{
				HitResultAABB result =
					player->GetAABB()->CheckAABB(enemy->GetAABB());

				if (result.isHit)
				{
					// プレイヤーダメージ
					player->Damage(1);

					// 敵も消す
					enemy->m_Dead = true;
				}
			}
		}
	}

	// Boss弾とPlayer衝突
	for (auto enemy : enemies)
	{
		Boss* boss = dynamic_cast<Boss*>(enemy);

		if (!boss) continue;

		for (auto bullet : boss->GetBullets())
		{
			if (!bullet->IsActive()) continue;

			if (player->GetAABB() && bullet->GetAABB())
			{
				HitResultAABB result =
					player->GetAABB()->CheckAABB(
						bullet->GetAABB()
					);

				if (result.isHit)
				{
					player->Damage(1);

					bullet->Destroy();
				}
			}
		}
	}

	// 死亡弾削除
	for (auto it = m_Bullets.begin(); it != m_Bullets.end(); )
	{
		if ((*it)->IsDead())
		{
			delete* it;
			it = m_Bullets.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void PlayScene::Draw()
{
	// 天球描画
	m_Skybox->Draw();
	PlayerManager::GetInstance()->Draw();
	EnemyManager::GetInstance()->Draw();
	CameraManager::GetInstance()->Draw();
	//m_Stage->Draw();
	//BlockManager::GetInstance()->Draw();

	Input::Draw();
	for (auto bullet : m_Bullets)
	{
		bullet->Draw();
	}

	CollisionManager::GetInstance()->Draw();

	// PlayerのHP表示
	Player* player = PlayerManager::GetInstance()->GetPlayer();

	DrawFormatString(
		20,
		20,
		GetColor(255, 255, 255),
		"HP : %d",
		player->GetHP()
	);

	// レーンの線を描画
	DrawLine3D(
		VGet(-15.0f, 0.01f, -50.0f),
		VGet(-15.0f, 0.01f, 100.0f),
		GetColor(255, 255, 255)
	);

	DrawLine3D(
		VGet(-5.0f, 0.01f, -50.0f),
		VGet(-5.0f, 0.01f, 100.0f),
		GetColor(255, 255, 255)
	);

	DrawLine3D(
		VGet(5.0f, 0.01f, -50.0f),
		VGet(5.0f, 0.01f, 100.0f),
		GetColor(255, 255, 255)
	);

	DrawLine3D(
		VGet(15.0f, 0.01f, -50.0f),
		VGet(15.0f, 0.01f, 100.0f),
		GetColor(255, 255, 255)
	);
}

void PlayScene::Fin()
{
	PlayerManager::DeleteInstance();
	CameraManager::DeleteInstance();
	//BlockManager::DeleteInstance();
	EnemyManager::DeleteInstance();
	delete m_SpawnManager;
	m_SpawnManager = nullptr;
	CollisionManager::DeleteInstance();
	for (auto bullet : m_Bullets)
	{
		delete bullet;
	}
	m_Bullets.clear();
	//delete m_Stage;
	// 天球削除
	delete m_Skybox;
}