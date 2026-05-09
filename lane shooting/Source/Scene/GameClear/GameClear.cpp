#include "DxLib.h"
#include "GameClear.h"
#include "../SceneManager.h"
#include "../../Input/Input.h"

GameClearScene::GameClearScene() : SceneBase()
{
}

GameClearScene::~GameClearScene()
{
}

void GameClearScene::Init()
{
}

void GameClearScene::Load()
{
}

void GameClearScene::Start()
{
}

void GameClearScene::Step()
{
    if (Input::IsTriggerKey(Input::KEY_Z))
    {
        SceneManager::GetInstance()->ChangeScene(TITLE);
    }
}

void GameClearScene::Update()
{
}

void GameClearScene::Draw()
{
    DrawString(600, 400, "GAME CLEAR!", GetColor(0, 255, 0));
}

void GameClearScene::Fin()
{
}