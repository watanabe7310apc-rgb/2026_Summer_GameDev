#include <DxLib.h>
#include <time.h>
#include "Application.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Manager/InputManager.h"

TitleScene::TitleScene(void) {

}

TitleScene::~TitleScene(void) {

}

void TitleScene::SystemInit(void) {

	imgTitle_ = LoadGraph("Image/Title2.PNG");
	imgStart_ = LoadGraph("Image/Start.png");

	Select_ = 0;

}

void TitleScene::GameInit(void) {

}

void TitleScene::Update(void) {

	InputManager& inputIns = InputManager::GetInstance();
	Application::GetInstance();

	//上下キーで選択
	if (inputIns.IsTrgDown(KEY_INPUT_UP)) {
		Select_--;
		if (Select_ < 0)Select_ = 1;
	}
	if (inputIns.IsTrgDown(KEY_INPUT_DOWN)) {
		Select_++;
		if (Select_ > 1)Select_ = 0;
	}

	//決定
	if (inputIns.IsTrgDown(KEY_INPUT_SPACE)) {
		if (Select_ == 1) {

			//back
			Application::GetInstance().SetGame(false);
		}
		else if(Select_==0){
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

void TitleScene::Draw(void) 
{
	// タイトル画像を画面中央に描画
	int w, h;
	GetGraphSize(imgTitle_, &w, &h);

	int x = (Application::SCREEN_SIZE_X - w) / 2;
	int y = (Application::SCREEN_SIZE_Y - h) / 2;

	DrawGraph(x, y, imgTitle_, true);

	switch (Select_)
	{
	case 0:
		DrawBox(((Application::SCREEN_SIZE_X - START_SIZE_X) / 2) - 10, (Application::SCREEN_SIZE_Y - 400) - 10, (Application::SCREEN_SIZE_X - START_SIZE_X) / 2 + START_SIZE_X + 10, (Application::SCREEN_SIZE_Y - 400) + 73, GetColor(255, 255, 0), true);
		break;
	case 1:
		DrawBox(((Application::SCREEN_SIZE_X - START_SIZE_X) / 2) - 10, (Application::SCREEN_SIZE_Y - 400) + 155, (Application::SCREEN_SIZE_X - START_SIZE_X) / 2 + START_SIZE_X + 10, (Application::SCREEN_SIZE_Y - 400) + 238, GetColor(255, 255, 0), true);
		break;
	}
	
	DrawGraph((Application::SCREEN_SIZE_X - START_SIZE_X) / 2, Application::SCREEN_SIZE_Y - 400, imgStart_, true);


}

void TitleScene::Release(void) 
{
	DeleteGraph(imgTitle_);
	DeleteGraph(imgStart_);
}

