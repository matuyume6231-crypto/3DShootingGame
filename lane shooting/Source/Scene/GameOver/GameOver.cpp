#include "GameOver.h"
#include "../SceneManager.h"
#include "DxLib.h"

void InitGameOverScene() {}
void LoadGameOverScene() {}
void StartGameOverScene() {}

void StepGameOverScene()
{
    if (CheckHitKey(KEY_INPUT_RETURN))
    {
        ChangeScene(SCENE_TITLE);
    }
}

void UpdateGameOverScene() {}

void DrawGameOverScene()
{
    DrawString(500, 300, "GAME OVER - PRESS ENTER", GetColor(255, 0, 0));
}

void FinGameOverScene() {}