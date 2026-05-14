#include "Player.h"
#include "DxLib.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Input/Input.h"



#define PLAYER_WIDTH	1.0f
#define PLAYER_HEIGHT	1.0f
#define PLAYER_DEPTH	1.0f

// コンストラクタ
Player::Player()
{
    m_Handle = 0;

    m_Lane = 1; // 中央

    m_LanePos[0] = -5.0f;
    m_LanePos[1] = 0.0f;
    m_LanePos[2] = 5.0f;

    m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_AABB = nullptr;
}

// デストラクタ
Player::~Player()
{
    // 終了処理を呼べば削除した時の後始末忘れを防げる
    Fin();
}

// 初期化
void Player::Init()
{
}

// ロード
void Player::Load()
{
    // 3Dモデルをロードする
    m_Handle = MV1LoadModel("Data/Player/Player.x");
}

void Player::Start()
{
	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.5f, 0.0f));
	m_AABB->SetSize(VGet(PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_DEPTH));
}

// ステップ
void Player::Step()
{

}


// 更新
void Player::Update()
{
	// 入力
	// 左を押した瞬間
	if (Input::IsTriggerKey(Input::KEY_LEFT))
	{
		if (m_Lane > 0) m_Lane--;
	}

	// 右を押した瞬間
	if (Input::IsTriggerKey(Input::KEY_RIGHT))
	{
		if (m_Lane < 2) m_Lane++;
	}

	// レーン位置反映
	m_Pos.x = m_LanePos[m_Lane];
	m_Pos.y = 0.0f;
	m_Pos.z = 0.0f;
}

// 描画
void Player::Draw()
{
	MV1SetPosition(m_Handle, m_Pos);
	// 3Dモデルを描画する
	MV1DrawModel(m_Handle);
}

void Player::Fin()
{
	if (m_AABB)
	{
		// CollisionManager側が管理しているので
		// m_AABB自体は削除しなくてOKな設計
		// ただしポインタは無効化する
		m_AABB = nullptr;
	}

	if (m_Handle != 0)
	{
		MV1DeleteModel(m_Handle);
		m_Handle = 0;
	}
}