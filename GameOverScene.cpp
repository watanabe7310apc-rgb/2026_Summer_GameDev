#include <DxLib.h>
#include "GameOverScene.h"
#include "Src/Application.h"
#include "Src/Manager/InputManager.h"
#include "Src/SceneManager.h"

GameOverScene::GameOverScene(void) {

	img_ = -1;
}

GameOverScene::~GameOverScene(void) {

}

void GameOverScene::SystemInit(void) {

	img_ = LoadGraph("image/UI/title.png");

}

void GameOverScene::GameInit(void) {

}

void GameOverScene::Update(void) {

	InputManager& inputIns = InputManager::GetInstance();

	// スペースキーorAボタン
	if (inputIns.IsNew(KEY_INPUT_SPACE) || inputIns.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN)) {
		SceneManager::GetInstance().ChangeScene(E_SCENE_ID::E_SCENE_TITLE);
	}
}

void GameOverScene::Draw(void)
{
	// タイトル画像を画面中央に描画
	int w, h;
	GetGraphSize(img_, &w, &h);

	int x = (Application::SCREEN_SIZE_X - w) / 2;
	int y = (Application::SCREEN_SIZE_Y - h) / 2;

	DrawGraph(x, y, img_, true);

	// テキスト表示
	DrawString(x, y + h + 20, "Press SPACE to Start", GetColor(255, 255, 255));
}

void GameOverScene::Release(void)
{
	DeleteGraph(img_);
}