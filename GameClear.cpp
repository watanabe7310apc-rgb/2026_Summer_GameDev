#include "GameClear.h"
#include <DxLib.h>
#include "Src/Application.h"
#include "Src/Manager/InputManager.h"
#include "Src/SceneManager.h"

GameClear::GameClear(void) {

	imgClear_ = -1;
}

GameClear::~GameClear(void) {

}

void GameClear::SystemInit(void) {

	imgClear_ = LoadGraph("Image/Clear.png");
}

void GameClear::GameInit(void) {

}

void GameClear::Update(void) {

	InputManager& inputIns = InputManager::GetInstance();

	// スペースキーorAボタン
	if (inputIns.IsNew(KEY_INPUT_SPACE) || inputIns.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN)) {
		SceneManager::GetInstance().ChangeScene(E_SCENE_ID::E_SCENE_TITLE);
	}
}

void GameClear::Draw(void)
{
	DrawGraph(0, 0, imgClear_, true);

	SetFontSize(64);

	DrawFormatString(Application::SCREEN_SIZE_X / 2 - 550, 900, GetColor(255, 0, 0), "SPACEキー/Aボタンを押してタイトルへ");


}


void GameClear::Release(void)
{
	DeleteGraph(imgClear_);
}
