#include "Player.h"
#include "DxLib.h"

// レーン位置
static float lanePos[3] = { -5.0f, 0.0f, 5.0f };

// プレイヤー本体
static Player player;

Player* GetPlayer()
{
    return &player;
}

void InitPlayer()
{
    player.lane = 1; // 中央
    player.x = lanePos[player.lane];
    player.y = 0.0f;
    player.z = 0.0f;
}

void UpdatePlayer()
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

void DrawPlayer()
{
    // 仮描画（2D）
    int screenX = 640 + (int)(player.x * 50);
    int screenY = 500;

    DrawBox(screenX - 20, screenY - 20, screenX + 20, screenY + 20, GetColor(0, 255, 0), TRUE);
}