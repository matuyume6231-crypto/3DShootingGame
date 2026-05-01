#include "DxLib.h"
#include "Play.h"
#include "../SceneManager.h"
#include "../../Player/Player.h"


void InitPlayScene() 
{
    InitPlayer();
}

void LoadPlayScene()
{

}

void StartPlayScene()
{

}

void StepPlayScene()
{
    // 仮：ESCでゲームオーバーへ
    if (CheckHitKey(KEY_INPUT_ESCAPE))
    {
        ChangeScene(SCENE_GAME_OVER);
    }

    // 仮：Cキーでクリア
    if (CheckHitKey(KEY_INPUT_C))
    {
        ChangeScene(SCENE_GAME_CLEAR);
    }
}

void UpdatePlayScene()
{
    UpdatePlayer();
}

void DrawPlayScene()
{
    DrawString(500, 300, "PLAY SCENE", GetColor(255, 255, 255));
    DrawPlayer();
}

void FinPlayScene() {}