#include "DxLib.h"
#include "GameClear.h"
#include "../SceneManager.h"
#include "../../Input/Input.h"
#include "../../Sound/SoundManager.h"

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
    // サウンド
    SoundManager::CreateInstance();
    SoundManager::GetInstance()->Load();
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
    SoundManager::GetInstance()->PlayClearBGM();
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
    SoundManager::GetInstance()->StopBGM();
    // 文字画像削除
    DeleteGraph(g_GameClearBG);
}