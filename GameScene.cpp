#include <DxLib.h>
#include "GameScene.h"
#include "Src/Application.h"
#include "Src/Manager/InputManager.h"

//コンストラクタ
GameScene::GameScene(void)
{

}

//デストラクタ
GameScene::~GameScene(void)
{

}

//初期化処理(最初の1回のみ実行)
void GameScene::SystemInit(void)
{
	front_ = new PlayerFront();
	front_->SystemInit();
}

//ゲーム起動・再開時に必ず呼び出す処理
void GameScene::GameInit(void)
{

}

//更新処理
void GameScene::Update(void)
{
	front_->Update();

}

//描画処理
void GameScene::Draw(void)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawBox(0, 0, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y,
		GetColor(0, 100, 200), true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawBox(0, Application::SCREEN_SIZE_Y*0.85, Application::SCREEN_SIZE_X, Application::SCREEN_SIZE_Y,
		GetColor(0, 200, 100), true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawBox(Application::SCREEN_SIZE_X*0.2, Application::SCREEN_SIZE_Y/3, 0, Application::SCREEN_SIZE_Y,
		GetColor(100, 100, 100), true);

	front_->Draw();
}

//解放処理(最後の1回のみ使用)
void GameScene::Release(void)
{
	front_->Release();
	delete front_;
}
