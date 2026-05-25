#include <DxLib.h>
#include <time.h>
#include "Application.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Manager/InputManager.h"

TitleScene::TitleScene(void) {

	imgTitle_ = -1;
}

TitleScene::~TitleScene(void) {

}

void TitleScene::SystemInit(void) {

	imgTitle_ = LoadGraph("image/UI/title.png");

}

void TitleScene::GameInit(void) {

}

void TitleScene::Update(void) {

	InputManager& inputIns = InputManager::GetInstance();

	// スペースキーorAボタン
	if (inputIns.IsNew(KEY_INPUT_SPACE) || inputIns.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN)) {
		SceneManager::GetInstance().ChangeScene(E_SCENE_ID::E_SCENE_GAME);
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