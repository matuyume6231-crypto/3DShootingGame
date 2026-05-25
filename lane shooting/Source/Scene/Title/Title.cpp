#include "DxLib.h"
#include "Title.h"
#include "../SceneManager.h"
#include "../../Input/Input.h"
#include "../../Sound/SoundManager.h"

// 画像
static int g_TitleHandle = -1;

TitleScene::TitleScene() : SceneBase()
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Init()
{
	// サウンド
	SoundManager::CreateInstance();
	SoundManager::GetInstance()->Load();
}

void TitleScene::Load()
{
	g_TitleHandle = LoadGraph("Data/Title/Title.png");
}

void TitleScene::Start()
{
	SoundManager::GetInstance()->PlayTitleBGM();
}

void TitleScene::Step()
{
	// Zキーでプレイシーンへ
	if (Input::IsTriggerKey(Input::KEY_Z))
	{
		SceneManager::GetInstance()->ChangeScene(PLAY);
	}
}

void TitleScene::Update()
{

}

void TitleScene::Draw()
{
	DrawString(0, 0, "タイトルシーン", GetColor(255, 255, 255));
	DrawGraph(0, 0, g_TitleHandle, TRUE);
}

void TitleScene::Fin()
{
	SoundManager::GetInstance()->StopBGM();
	DeleteGraph(g_TitleHandle);
}