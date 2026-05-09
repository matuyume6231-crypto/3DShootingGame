#include "DxLib.h"
#include "Title.h"
#include "../SceneManager.h"
#include "../../Input/Input.h"

TitleScene::TitleScene() : SceneBase()
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Init()
{

}

void TitleScene::Load()
{

}

void TitleScene::Start()
{

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
}

void TitleScene::Fin()
{

}