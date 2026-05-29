#include <DxLib.h>
#include "Application.h"
#include "SceneManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	imgTitle_ = LoadGraph("Image/UI/Title.png");
	imgStart_ = LoadGraph("Image/UI/HitStartKey.png");
}

void TitleScene::Update(void)
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		//スペースキーが押下されたら、ゲームシーンへ遷移する
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}
}

void TitleScene::Draw(void)
{

	//タイトル画像のサイズ 600×250
	//画面真ん中のちょっと上
	DrawGraph(
		(Application::SCREEN_SIZE_X / 2) - (600 / 2),
		(Application::SCREEN_SIZE_Y / 2) - (250 / 2) - 100,
		imgTitle_,
		true
	);

	//スタートキー画像のサイズ 337×53
	//画面真ん中のちょっと下
	DrawGraph(
		(Application::SCREEN_SIZE_X / 2) - (337 / 2),
		(Application::SCREEN_SIZE_Y / 2) - (53 / 2) + 100,
		imgStart_,
		true
	);

}

void TitleScene::Release(void)
{
	DeleteGraph(imgTitle_);
	DeleteGraph(imgStart_);
}