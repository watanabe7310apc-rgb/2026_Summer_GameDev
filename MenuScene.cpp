#include "MenuScene.h"
#include <DxLib.h>
#include <time.h>
#include "Src/Application.h"
#include "Src/SceneManager.h"
#include "Src/Manager/InputManager.h"

MenuScene::MenuScene(void) {

}

MenuScene::~MenuScene(void) {

}

void MenuScene::SystemInit(void) {

	imgSelect_ = LoadGraph("Image/LevelSelect.PNG");
	imgHaikei_ = LoadGraph("Image/SelectHaikei.jpg");

	Select_ = 0;

}

void MenuScene::GameInit(void) {

}

void MenuScene::Update(void) {

	InputManager& inputIns = InputManager::GetInstance();
	Application::GetInstance();

	//上下キーで選択
	if (inputIns.IsTrgDown(KEY_INPUT_UP)) {
		Select_--;
		if (Select_ < 0)Select_ = 1;
	}
 	if (inputIns.IsTrgDown(KEY_INPUT_DOWN)) {
		Select_++;
		if (Select_ > 2)Select_ = 0;
	}

	//決定
	if (inputIns.IsTrgDown(KEY_INPUT_SPACE)) {
		if (Select_ == 1) {

			//back
			SceneManager::GetInstance().ChangeScene(E_SCENE_ID::E_SCENE_TITLE);
		}
		else if (Select_ == 0) {
			PlaySoundFile("Image/Sound/SceneChange.mp3", DX_PLAYTYPE_BACK);
			//ステージ番号をゲームへ渡す
			SceneManager::GetInstance().ChangeScene(E_SCENE_ID::E_SCENE_GAME);
		}
	}

	// スペースキーorAボタン
	//if (inputIns.IsNew(KEY_INPUT_SPACE) || inputIns.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN)) {
	//	SceneManager::GetInstance().ChangeScene(E_SCENE_ID::E_SCENE_GAME);
	//}

}

void MenuScene::Draw(void)
{
	// タイトル画像を画面中央に描画
	int w, h;
	GetGraphSize(imgHaikei_, &w, &h);

	int x = (Application::SCREEN_SIZE_X - w) / 2;
	int y = (Application::SCREEN_SIZE_Y - h) / 2;

	DrawGraph(x, y, imgHaikei_, true);

	switch (Select_)
	{
	case 0:
		DrawBox(((Application::SCREEN_SIZE_X - TITLE_SIZE_X) / 2) - 10, (Application::SCREEN_SIZE_Y - TITLE_SIZE_Y - (TITLE_SIZE_Y / 2)) - 10, (Application::SCREEN_SIZE_X - TITLE_SIZE_X)/2+TITLE_SIZE_X + 10, (Application::SCREEN_SIZE_Y - TITLE_SIZE_Y - (TITLE_SIZE_Y / 2)) + 113, GetColor(255, 255, 0), true);
		break;
	case 1:
		DrawBox(((Application::SCREEN_SIZE_X - TITLE_SIZE_X) / 2) - 10, (Application::SCREEN_SIZE_Y - TITLE_SIZE_Y - (TITLE_SIZE_Y / 2)+148) - 10, (Application::SCREEN_SIZE_X - TITLE_SIZE_X) / 2 + TITLE_SIZE_X + 10, (Application::SCREEN_SIZE_Y - TITLE_SIZE_Y - (TITLE_SIZE_Y / 2)) + 257, GetColor(255, 255, 0), true);
		break;
	case 2:
		DrawBox(((Application::SCREEN_SIZE_X - TITLE_SIZE_X) / 2) - 10, (Application::SCREEN_SIZE_Y - TITLE_SIZE_Y - (TITLE_SIZE_Y / 2)+302) - 10, (Application::SCREEN_SIZE_X - TITLE_SIZE_X) / 2 + TITLE_SIZE_X + 10, (Application::SCREEN_SIZE_Y - TITLE_SIZE_Y - (TITLE_SIZE_Y / 2)) + 412, GetColor(255, 255, 0), true);
		break;
	}

	DrawGraph((Application::SCREEN_SIZE_X - TITLE_SIZE_X) / 2, Application::SCREEN_SIZE_Y - TITLE_SIZE_Y-(TITLE_SIZE_Y/2), imgSelect_, true);

}

void MenuScene::Release(void)
{
	DeleteGraph(imgHaikei_);
	DeleteGraph(imgSelect_);
}
