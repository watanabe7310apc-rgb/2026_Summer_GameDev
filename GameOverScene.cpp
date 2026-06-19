#include <DxLib.h>
#include "GameOverScene.h"
#include "Src/Application.h"
#include "Src/Manager/InputManager.h"
#include "Src/SceneManager.h"

GameOverScene::GameOverScene(void) {

	imgGameOver_ = -1;
}

GameOverScene::~GameOverScene(void) {

}

void GameOverScene::SystemInit(void) {

	imgGameOver_ = LoadGraph("image/GameOver.png");
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
		DrawGraph(0, 0, imgGameOver_, true);
		SetFontSize(64);

		DrawFormatString(Application::SCREEN_SIZE_X / 2 - 550, 900, GetColor(255, 0, 0), "SPACEキー/Aボタンを押してタイトルへ");

}


void GameOverScene::Release(void)
{
	DeleteGraph(imgGameOver_);
}