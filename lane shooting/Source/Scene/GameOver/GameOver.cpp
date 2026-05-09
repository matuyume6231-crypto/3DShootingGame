#include "DxLib.h"
#include "GameOver.h"
#include "../SceneManager.h"
#include "../../Input/Input.h"

GameOverScene::GameOverScene() : SceneBase()
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::Init()
{
}

void GameOverScene::Load()
{
}

void GameOverScene::Start()
{
}

void GameOverScene::Step()
{
    // Z‚Åƒ^ƒCƒgƒ‹‚Ö–ß‚é
    if (Input::IsTriggerKey(Input::KEY_Z))
    {
        SceneManager::GetInstance()->ChangeScene(TITLE);
    }
}

void GameOverScene::Update()
{
}

void GameOverScene::Draw()
{
    DrawString(600, 400, "GAME OVER", GetColor(255, 0, 0));
}

void GameOverScene::Fin()
{
}