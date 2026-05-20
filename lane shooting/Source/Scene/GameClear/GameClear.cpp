#include "DxLib.h"
#include "GameClear.h"
#include "../SceneManager.h"
#include "../../Input/Input.h"

// GameClear画像
int g_GameClearBG = 0;

GameClearScene::GameClearScene() : SceneBase()
{
}

GameClearScene::~GameClearScene()
{
}

void GameClearScene::Init()
{
    // 文字画像ハンドル初期化
    g_GameClearBG = 0;
}

void GameClearScene::Load()
{
    // 背景ロード
    g_GameClearBG = LoadGraph("Data/GameClear/GameClear.png");
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
    DrawGraph(0, 0, g_GameClearBG, TRUE);
}

void GameClearScene::Fin()
{
    // 文字画像削除
    DeleteGraph(g_GameClearBG);
}