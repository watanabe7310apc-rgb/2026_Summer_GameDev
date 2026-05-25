#include <DxLib.h>
#include <time.h>
#include "Application.h"
#include "SceneManager.h"
#include "TitleScene.h"

TitleScene::TitleScene(void) {

	imgTitle_ = -1;
}

TitleScene::~TitleScene(void) {

}

void TitleScene::SystemInit(void) {

	imgTitle_ = LoadGraph("image/UI/title.png");

}

void TitleScene::GameInit(void) {

	// 次のシーンの初期設定
	nextSceneID = E_SCENE_TITLE;

	prevSpaceKey = nowSpaceKey = 0;

	prevPadKey = nowPadKey = 0;
}

void TitleScene::Update(void) {
	// スペースキー
	prevSpaceKey = nowSpaceKey;
	nowSpaceKey = CheckHitKey(KEY_INPUT_SPACE);

	// ゲームパッドボタン
	prevPadKey = nowPadKey;
	nowPadKey = GetJoypadInputState(DX_INPUT_KEY_PAD1) & PAD_INPUT_1;

	// スペースキーのアップトリガー
	bool spaceUp = (prevSpaceKey == 1 && nowSpaceKey == 0);

	// パッドボタンのアップトリガー
	bool padUp = (prevPadKey != 0 && nowPadKey == 0);

	if (spaceUp || padUp) {
		nextSceneID = E_SCENE_GAME;
	}
}

void TitleScene::Draw(void) 
{
	// タイトル画像を画面中央に描画
	int w, h;
	GetGraphSize(imgTitle_, &w, &h);

	int x = (Application::SCREEN_SIZE_X - w) / 2;
	int y = (Application::SCREEN_SIZE_Y - h) / 2;

	DrawGraph(x, y, imgTitle_, true);

	// テキスト表示
	DrawString(x, y + h + 20, "Press SPACE to Start", GetColor(255, 255, 255));
}

void TitleScene::Release(void) 
{
	DeleteGraph(imgTitle_);
}