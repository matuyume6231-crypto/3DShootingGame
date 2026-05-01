#include "Title.h"
#include "../SceneManager.h"
#include "DxLib.h"

void InitTitleScene()
{
}

void LoadTitleScene()
{
}

void StartTitleScene()
{
}

void StepTitleScene()
{
    // “ü—Í
    if (CheckHitKey(KEY_INPUT_RETURN))
    {
        ChangeScene(SCENE_PLAY);
    }
}

void UpdateTitleScene()
{
}

void DrawTitleScene()
{
    DrawString(500, 300, "TITLE - PRESS ENTER", GetColor(255, 255, 255));
}

void FinTitleScene()
{
}