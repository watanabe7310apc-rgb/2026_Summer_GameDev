#include "MenuScene.h"
#include <DxLib.h>
#include <time.h>
#include "Src/Application.h"
#include "Src/SceneManager.h"
#include "Src/Manager/InputManager.h"
#include "GameScene.h"

MenuScene::MenuScene(void) {

}

MenuScene::~MenuScene(void) {

}

void MenuScene::SystemInit(void) {

	imgSelect_ = LoadGraph("Image/LevelSelect.PNG");
	imgHaikei_ = LoadGraph("Image/SelectHaikei.jpg");
	imgBack_ = LoadGraph("Image/Back.png");
	imgPlayerSelect_ = LoadGraph("Image/PlayerSelect.png");

	Select_ = 1;
	Slide_ = false;
	Next_ = false;
}

void MenuScene::GameInit(void) {

}

void MenuScene::Update(void) {

	InputManager& inputIns = InputManager::GetInstance();
	Application::GetInstance();

	InputManager::JOYPAD_IN_STATE state =
		inputIns.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);

	int analogKeyY = state.AKeyLY;
	int analogKeyX = state.AKeyLX;

	if (!Next_) {
		//上下キーで選択
		if (inputIns.IsTrgDown(KEY_INPUT_UP) || analogKeyY < 0 && !Slide_) {
			Select_--;
			if (Select_ < 1)Select_ = 3;
		}
		if (inputIns.IsTrgDown(KEY_INPUT_DOWN) || analogKeyY > 0 && !Slide_) {
			Select_++;
			if (Select_ > 4)Select_ = 4;
		}

		if (inputIns.IsTrgDown(KEY_INPUT_LEFT) || analogKeyX < 0 && !Slide_) {
			Select_ = 4;
		}

		if (inputIns.IsTrgDown(KEY_INPUT_RIGHT) || analogKeyX > 0 && !Slide_) {
			Select_ = 1;

		}

		if (analogKeyY < 0 || analogKeyY > 0 || analogKeyX > 0 || analogKeyX < 0 && !Slide_)
		{
			Slide_ = true;
		}

		else if (analogKeyY == 0 && Slide_)
		{
			Slide_ = false;
		}
	}
	else {
		//左右キーで選択
		if (inputIns.IsTrgDown(KEY_INPUT_LEFT) || analogKeyX < 0 && !Slide_) {
			Select_--;
			if (Select_ < 1)Select_ = 2;
		}
		if (inputIns.IsTrgDown(KEY_INPUT_RIGHT) || analogKeyX > 0 && !Slide_) {
			Select_++;
			if (Select_ > 2)Select_ = 1;
		}
		if (inputIns.IsTrgDown(KEY_INPUT_DOWN) || analogKeyY < 0 && !Slide_) {
			Select_ = 3;
		}
		if (inputIns.IsTrgDown(KEY_INPUT_UP) || analogKeyY > 0 && !Slide_) {
			Select_ = 1;
		}

	}

	if (!Next_) {
		//決定
		if (inputIns.IsTrgDown(KEY_INPUT_SPACE) || inputIns.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN)) {
			switch (Select_) {
			case (1):
				PlaySoundFile("Image/Sound/SceneChange.mp3", DX_PLAYTYPE_BACK);
				//ステージ番号をゲームへ渡す
				//SceneManager::GetInstance().ChangeScene(E_SCENE_ID::E_SCENE_GAME);
				Next_ = true;

				Application::Level_ = Select_;

				Select_ = 1;

				break;

			case (2):
				PlaySoundFile("Image/Sound/SceneChange.mp3", DX_PLAYTYPE_BACK);
				//ステージ番号をゲームへ渡す
				//SceneManager::GetInstance().ChangeScene(E_SCENE_ID::E_SCENE_GAME);
				Next_ = true;

				Application::Level_ = Select_;

				Select_ = 1;

				break;

			case (3):
				PlaySoundFile("Image/Sound/SceneChange.mp3", DX_PLAYTYPE_BACK);
				//ステージ番号をゲームへ渡す
				//SceneManager::GetInstance().ChangeScene(E_SCENE_ID::E_SCENE_GAME);
				Next_ = true;
				Application::Level_ = Select_;

				Select_ = 1;
				break;

			case(4):
				PlaySoundFile("Image/Sound/SceneChange.mp3", DX_PLAYTYPE_BACK);
				//back
				SceneManager::GetInstance().ChangeScene(E_SCENE_ID::E_SCENE_TITLE);
				break;
			}
		}
	}
	else  {
		if(inputIns.IsTrgDown(KEY_INPUT_SPACE) || inputIns.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
		switch (Select_) {
		case (1):
			PlaySoundFile("Image/Sound/SceneChange.mp3", DX_PLAYTYPE_BACK);
			//ステージ番号をゲームへ渡す
			SceneManager::GetInstance().ChangeScene(E_SCENE_ID::E_SCENE_GAME);

			break;

		case (2):
			PlaySoundFile("Image/Sound/SceneChange.mp3", DX_PLAYTYPE_BACK);
			//ステージ番号をゲームへ渡す
			SceneManager::GetInstance().ChangeScene(E_SCENE_ID::E_SCENE_GAME);

			break;

		case (3):
			Next_=false;

			break;
		}
	}
	
	//スペースだと開始できないのでTABキーを押してゲームをスタートしてください
	if (inputIns.IsTrgDown(KEY_INPUT_TAB)) {
		SceneManager::GetInstance().ChangeScene(E_SCENE_ID::E_SCENE_GAME);
		Application::Level_ = Select_;

	}
}

void MenuScene::Draw(void)
{
	// タイトル画像を画面中央に描画
	int w, h;
	GetGraphSize(imgHaikei_, &w, &h);

	int x = (Application::SCREEN_SIZE_X - w) / 2;
	int y = (Application::SCREEN_SIZE_Y - h) / 2;

	DrawGraph(x, y, imgHaikei_, true);
	if (!Next_) {
	switch (Select_)
	{
	case 1:
		DrawBox(((Application::SCREEN_SIZE_X - TITLE_SIZE_X) / 2) - 10, (Application::SCREEN_SIZE_Y - TITLE_SIZE_Y - (TITLE_SIZE_Y / 2)) - 10, (Application::SCREEN_SIZE_X - TITLE_SIZE_X)/2+TITLE_SIZE_X + 10, (Application::SCREEN_SIZE_Y - TITLE_SIZE_Y - (TITLE_SIZE_Y / 2)) + 113, GetColor(255, 255, 0), true);
		break;
	case 2:
		DrawBox(((Application::SCREEN_SIZE_X - TITLE_SIZE_X) / 2) - 10, (Application::SCREEN_SIZE_Y - TITLE_SIZE_Y - (TITLE_SIZE_Y / 2)+148) - 10, (Application::SCREEN_SIZE_X - TITLE_SIZE_X) / 2 + TITLE_SIZE_X + 10, (Application::SCREEN_SIZE_Y - TITLE_SIZE_Y - (TITLE_SIZE_Y / 2)) + 257, GetColor(255, 255, 0), true);
		break;
	case 3:
		DrawBox(((Application::SCREEN_SIZE_X - TITLE_SIZE_X) / 2) - 10, (Application::SCREEN_SIZE_Y - TITLE_SIZE_Y - (TITLE_SIZE_Y / 2)+302) - 10, (Application::SCREEN_SIZE_X - TITLE_SIZE_X) / 2 + TITLE_SIZE_X + 10, (Application::SCREEN_SIZE_Y - TITLE_SIZE_Y - (TITLE_SIZE_Y / 2)) + 412, GetColor(255, 255, 0), true);
		break;
	case 4:
		DrawBox(Application::SCREEN_SIZE_X / 9 - 10,Application::SCREEN_SIZE_Y - 140, Application::SCREEN_SIZE_X / 9 + 260, Application::SCREEN_SIZE_Y - 40, GetColor(255, 255, 0), true);
		break;
	}

		DrawGraph((Application::SCREEN_SIZE_X - TITLE_SIZE_X) / 2, Application::SCREEN_SIZE_Y - TITLE_SIZE_Y - (TITLE_SIZE_Y / 2), imgSelect_, true);
	}
	else if (Next_)
	{
		switch (Select_)
		{
		case 1:
			DrawBox((Application::SCREEN_SIZE_X - 597) / 2 - 10, Application::SCREEN_SIZE_Y / 2 - 130, (Application::SCREEN_SIZE_X - 597) / 2 + 276, Application::SCREEN_SIZE_Y / 2 + 10 , GetColor(255, 255, 0), true);
			break;
		case 2:
			DrawBox(Application::SCREEN_SIZE_X - 939, Application::SCREEN_SIZE_Y / 2 - 130, Application::SCREEN_SIZE_X - 653, Application::SCREEN_SIZE_Y / 2 + 10, GetColor(255, 255, 0), true);
			break;
		case 3:
			DrawBox(Application::SCREEN_SIZE_X / 9 - 10, Application::SCREEN_SIZE_Y - 140, Application::SCREEN_SIZE_X / 9 + 260, Application::SCREEN_SIZE_Y - 40, GetColor(255, 255, 0), true);
		}

		DrawGraph((Application::SCREEN_SIZE_X - 597) / 2, Application::SCREEN_SIZE_Y / 2 - 120, imgPlayerSelect_, true);
	}
	DrawGraph(Application::SCREEN_SIZE_X / 9, Application::SCREEN_SIZE_Y - 130, imgBack_, true);

}

void MenuScene::Release(void)
{
	DeleteGraph(imgHaikei_);
	DeleteGraph(imgSelect_);
	DeleteGraph(imgBack_);
	DeleteGraph(imgPlayerSelect_);
}
