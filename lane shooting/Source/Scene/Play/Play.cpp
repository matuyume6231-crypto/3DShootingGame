#include "DxLib.h"
#include "Play.h"
#include "../SceneManager.h"
#include "../../Player/Player.h"
#include "../../Stage/Stage.h"

void InitPlayScene()
{
    InitStage();
    
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
    UpdateStage();
}

void DrawPlayScene()
{
    DrawStage();
}

void FinPlayScene() {}