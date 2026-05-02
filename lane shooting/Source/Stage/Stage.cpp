#include "Stage.h"
#include "DxLib.h"

static float scroll = 0.0f;

void InitStage()
{
    scroll = 0.0f;
}

void UpdateStage()
{
    // 前に進んでいるように見せる
    scroll += 5.0f;
    if (scroll > 100) scroll = 0;
}

void DrawStage()
{
    int centerX = 640;

    // 床（簡易）
    DrawBox(0, 400, 1280, 720, GetColor(50, 50, 50), TRUE);

    // レーン線（スクロール演出）
    for (int i = 0; i < 10; i++)
    {
        int y = 400 + (int)(i * 40 + scroll) % 400;

        // 左レーン境界
        DrawLine(centerX - 100, y, centerX - 100, y + 20, GetColor(255, 255, 255));

        // 右レーン境界
        DrawLine(centerX + 100, y, centerX + 100, y + 20, GetColor(255, 255, 255));
    }
}