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

PlayScene::PlayScene() : SceneBase()
{
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

	// ブロック
	//BlockManager::CreateInstance();
	//BlockManager::GetInstance()->Init();

	// 敵
	EnemyManager::CreateInstance();
	EnemyManager::GetInstance()->Init();
}

void PlayScene::Load()
{
	PlayerManager::GetInstance()->Load();
	CameraManager::GetInstance()->Load();
	EnemyManager::GetInstance()->Load();

	//m_Stage->Load();
}

void PlayScene::Start()
{
	PlayerManager::GetInstance()->Start();
	CameraManager::GetInstance()->Start();
	EnemyManager::GetInstance()->Start();

	//m_Stage->Start();

	// 敵生成
	EnemyManager* enemyManager = EnemyManager::GetInstance();
	EnemyBase* enemy = enemyManager->CreateEnemy(YELLOW_ENEMY);
	//enemy->SetPos(VGet(3.0f, 1.0f, 0.0f));

}

void PlayScene::Step()
{
	CameraManager* camera = CameraManager::GetInstance();

	PlayerManager::GetInstance()->Step();
	EnemyManager::GetInstance()->Step();
	camera->Step();
	//m_Stage->Step();
	//BlockManager::GetInstance()->Step();

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

	// 弾更新
	for (auto bullet : m_Bullets)
	{
		bullet->Update();
	}
}

void PlayScene::Update()
{
	CameraManager* camera = CameraManager::GetInstance();

	PlayerManager::GetInstance()->Update();
	EnemyManager::GetInstance()->Update();
	camera->Update();
	//m_Stage->Update();
	//BlockManager::GetInstance()->Update();

	for (auto bullet : m_Bullets)
	{
		bullet->Update();
	}
	// 衝突処理
	auto& enemies = EnemyManager::GetInstance()->GetEnemyList();

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

					// 敵を死亡扱い
					enemy->m_Dead = true;

					break; // この弾は終了
				}
			}
		}
	}
}

void PlayScene::Draw()
{
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
}

void PlayScene::Fin()
{
	PlayerManager::DeleteInstance();
	CameraManager::DeleteInstance();
	//BlockManager::DeleteInstance();
	EnemyManager::DeleteInstance();
	CollisionManager::DeleteInstance();
	for (auto bullet : m_Bullets)
	{
		delete bullet;
	}
	m_Bullets.clear();
	//delete m_Stage;
}