#include "GameClear.h"
#include "../SceneManager.h"
#include "DxLib.h"

void InitGameClearScene() {}
void LoadGameClearScene() {}
void StartGameClearScene() {}

void StepGameClearScene()
{
    if (CheckHitKey(KEY_INPUT_RETURN))
    {
        ChangeScene(SCENE_TITLE);
    }
}

void UpdateGameClearScene() {}

void DrawGameClearScene()
{
    DrawString(500, 300, "GAME CLEAR!", GetColor(0, 255, 0));
}

void FinGameClearScene() {}