#include "Player.h"
#include "DxLib.h"

// レーン位置
static float lanePos[3] = { -5.0f, 0.0f, 5.0f };

// プレイヤー本体
static Player player;

// コンストラクタ
Player::Player()
{
    m_Handle = 0;
    player.lane = 1; // 中央
    player.x = lanePos[player.lane];
    player.y = 0.0f;
    player.z = 0.0f;
    //m_Pos = VGet(0.0f, 1.0f, -3.0f);
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

}

// ステップ
void Player::Step()
{

}


// 更新
void Player::Update()
{
    // 入力
    if (CheckHitKey(KEY_INPUT_LEFT) && player.lane > 0)
    {
        player.lane--;
    }
    if (CheckHitKey(KEY_INPUT_RIGHT) && player.lane < 2)
    {
        player.lane++;
    }

    // レーンに応じて位置更新
    player.x = lanePos[player.lane];
}

// 描画
void Player::Draw()
{
	// 3Dモデルを描画する
	MV1DrawModel(m_Handle);

	// 座標を描画する
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "座標[%f, %f, %f]", m_Pos.x, m_Pos.y, m_Pos.z);
}