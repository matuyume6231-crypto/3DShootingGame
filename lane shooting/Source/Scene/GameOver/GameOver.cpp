#include "DxLib.h"
#include "GameOver.h"
#include "../SceneManager.h"
#include "../../Input/Input.h"

// GameOver文字画像ハンドル
int g_GameOverHandle = 0;

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
    // GameOver画像
    g_GameOverHandle = LoadGraph("Data/GameOver/GameOver.png");
}

void GameOverScene::Start()
{
}

void GameOverScene::Step()
{
    // Zでタイトルへ戻る
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
    // GameOver文字画像描画
    DrawGraph(0, 0, g_GameOverHandle, TRUE);
}

void GameOverScene::Fin()
{
    // 文字画像削除
    DeleteGraph(g_GameOverHandle);
}